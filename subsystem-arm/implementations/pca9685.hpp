#pragma once

#include "module.hpp"
#include "peripherals/i2c.hpp"
#include "utility/math/bit.hpp"
#include "utility/enum.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"

namespace sjsu
{
struct pca9685Settings_t
{
  /// Typical Frequency of a generic hobby RC servo.
  units::frequency::hertz_t frequency = 50_Hz;
  /// Typical Min Angle of a generic hobby RC servo.
  units::angle::degree_t min_angle = 0_deg;
  /// Typical Max Angle of a generic hobby RC servo.
  units::angle::degree_t max_angle = 90_deg;
  /// Typical Min Pulse of a generic hobby RC servo.
  std::chrono::microseconds min_pulse = 500us;
  /// Typical Max Pulse of a generic hobby RC servo.
  std::chrono::microseconds max_pulse = 2500us;

  /// Sets the minimum and maximum pulse width lengths that the class will use
  /// to clamp its pulse width output when using SetAngle.
  ///
  /// @param new_min_pulse - the minimum pulse width that the servo can handle.
  /// @param new_max_pulse - the maximum pulse width that the servo can handle.
  auto & PulseBounds(std::chrono::microseconds new_min_pulse,
                     std::chrono::microseconds new_max_pulse)
  {
    min_pulse = new_min_pulse;
    max_pulse = new_max_pulse;
    return *this;
  }

  /// Sets your angle bounds that maps angles to microseconds when using
  /// SetAngle.
  ///
  /// @param new_min_angle - The minimum angle to limit the servo to.
  /// @param new_max_angle - The maximum angle to limit the servo to.
  auto & AngleBounds(units::angle::degree_t new_min_angle,
                     units::angle::degree_t new_max_angle)
  {
    min_angle = new_min_angle;
    max_angle = new_max_angle;
    return *this;
  }
};

/// Driver for the PCA9685 I2C to PWM controller
class Pca9685 : public Module<pca9685Settings_t>
{
 public:
  /// Map of all of the used device addresses in this driver.
  enum class RegisterMap : uint8_t
  {
    /// Config to set restart, extclk, auto-increment, sleep, subaddress and
    /// allcall responses
    kModeRegister1 = 0x00,

    /// Device configuration starting address
    kAllOutputAddress = 0x05,

    /// Register address of the the first byte of the first pwm output
    kOutputAddress0 = 0x06,

    /// Prescaler to change output frequency
    kPrescaler = 0xFE
  };

  /// PCA9685 Constructor
  ///
  /// @param i2c - i2c peripheral used to commnicate with device.
  /// @param address - PCA9685 device address.
  explicit constexpr Pca9685(I2c & i2c, uint8_t address = 0x40)
      : i2c_(i2c), kAddress(address)
  {
  }

  void ModuleInitialize() override
  {
    i2c_.Initialize();
    setFrequency(50_Hz);
    // Wake up the device
    ActiveMode(true);
  }

  void ModulePowerDown() override
  {
    // Put device into standby so we can configure the device.
    ActiveMode(false);
  }

  void setFrequency(units::frequency::hertz_t outputFrequency)
  {
    // Note that the PCA9685 has in internal oscilator frenquency of 25MHz, if
    // an externall oscilator is used, the prescale value must be different.
    uint8_t prescaleValue = static_cast<uint8_t>(
        round((25_MHz / (4096 * outputFrequency)).to<float>()) - 1);
    i2c_.Write(kAddress, { static_cast<uint8_t>(Value(RegisterMap::kPrescaler)),
                           prescaleValue });
  }

  // The delay can be used to stagger the outputs, to minimize current spikes.
  void SetDutyCycle(uint8_t outputNumber, float duty_cycle, float delay = 0.0f)
  {
    if (delay + duty_cycle > 1)
    {
      throw Exception(std::errc::invalid_argument,
                      "delay + duty cycle cannot be greater than 100%");
      /// Actually it can, see PCA9685 documentation to implement (p.17).
    }
    uint16_t onTime = 0;
    // this does nothing? Might need to delete upon further testing
    // delay == 0 ? 0 : static_cast<uint16_t>(4096.f * delay + 0.5f) - 1;

    uint16_t offTime =
        static_cast<uint16_t>((4096.f * duty_cycle + 0.5f) + onTime);
    setPWM(outputNumber, onTime, offTime);
  }

  void setPulseWidth(uint8_t outputNumber, units::time::second_t pulseLength)
  {
    uint16_t offTime = (pulseLength * settings.frequency * 4096).to<uint16_t>();
    setPWM(outputNumber, 0, offTime);
  }

  void fullOn(uint8_t outputNumber)
  {
    if (outputNumber > 15)
    {
      throw Exception(std::errc::invalid_argument,
                      "Invalid Output Number. Must be between 0-15");
    }

    constexpr auto kOperateBit = bit::MaskFromRange(4);
    uint8_t onData;
    uint8_t offData;
    i2c_.WriteThenRead(
        kAddress,
        { static_cast<uint8_t>(4 * outputNumber +
                               Value(RegisterMap::kOutputAddress0) + 1) },
        &onData, 1);
    i2c_.WriteThenRead(
        kAddress,
        { static_cast<uint8_t>(4 * outputNumber +
                               Value(RegisterMap::kOutputAddress0) + 3) },
        &offData, 1);

    onData  = bit::Insert(onData, true, kOperateBit);    // Set full-on
    offData = bit::Insert(offData, false, kOperateBit);  // Disable

    // Disable the full-off bit, then turn on the full-on bit
    i2c_.Write(kAddress,
               { static_cast<uint8_t>(4 * outputNumber +
                                      Value(RegisterMap::kOutputAddress0) + 3),
                 offData });
    i2c_.Write(kAddress,
               { static_cast<uint8_t>(4 * outputNumber +
                                      Value(RegisterMap::kOutputAddress0) + 1),
                 onData });
  }

  void fullOff(uint8_t outputNumber)
  {
    if (outputNumber > 15)
    {
      throw Exception(std::errc::invalid_argument,
                      "Invalid Output Number. Must be between 0-15");
    }
    constexpr auto kOperateBit = bit::MaskFromRange(4);

    uint8_t offData;
    i2c_.WriteThenRead(
        kAddress,
        { static_cast<uint8_t>(4 * outputNumber +
                               Value(RegisterMap::kOutputAddress0) + 3) },
        &offData, 1);
    offData = bit::Insert(offData, true, kOperateBit);  // Enable full off
    i2c_.Write(kAddress,
               { static_cast<uint8_t>(4 * outputNumber +
                                      Value(RegisterMap::kOutputAddress0) + 3),
                 offData });
  }

 private:
  void ActiveMode(bool is_active = true)
  {
    constexpr auto kSleepMask = bit::MaskFromRange(4);

    uint8_t modeRegData;
    i2c_.WriteThenRead(kAddress, { Value(RegisterMap::kModeRegister1) },
                       &modeRegData, 1);

    // !is_active is required as the bit must be set to 0 in order to prevent it
    // from sleeping.
    modeRegData = bit::Insert(modeRegData, !is_active, kSleepMask);

    // Write enable sequence
    i2c_.Write(kAddress, { Value(RegisterMap::kModeRegister1), modeRegData });
  }

  void setPWM(uint8_t outputNumber, uint16_t onTime, uint16_t offTime)
  {
    uint8_t onTimeH = static_cast<uint8_t>(onTime >> 8);
    uint8_t onTimeL = static_cast<uint8_t>(onTime & 0xFF);

    uint8_t offTimeH = static_cast<uint8_t>(offTime >> 8);
    uint8_t offTimeL = static_cast<uint8_t>(offTime & 0xFF);

    i2c_.Write(kAddress,
               { static_cast<uint8_t>(4 * outputNumber +
                                      Value(RegisterMap::kOutputAddress0)),
                 onTimeL });
    i2c_.Write(kAddress,
               { static_cast<uint8_t>(4 * outputNumber +
                                      Value(RegisterMap::kOutputAddress0) + 1),
                 onTimeH });
    i2c_.Write(kAddress,
               { static_cast<uint8_t>(4 * outputNumber +
                                      Value(RegisterMap::kOutputAddress0) + 2),
                 offTimeL });
    i2c_.Write(kAddress,
               { static_cast<uint8_t>(4 * outputNumber +
                                      Value(RegisterMap::kOutputAddress0) + 3),
                 offTimeH });
  }

  I2c & i2c_;
  const uint8_t kAddress;
};
}  // namespace sjsu