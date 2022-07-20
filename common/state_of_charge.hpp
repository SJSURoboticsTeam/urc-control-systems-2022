#include "devices/sensors/battery/max17043.hpp"
#include "peripherals/lpc17xx/i2c.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
#include "peripherals/hardware_counter.hpp"
namespace sjsu::common
{
/// State of charge manages ltc4150 and max17043
class StateOfCharge
{
 public:
  StateOfCharge() {}
  sjsu::lpc40xx::I2c & i2c        = sjsu::lpc40xx::GetI2c<2>();
  sjsu::lpc40xx::Gpio & alert_pin = sjsu::lpc40xx::GetGpio<0, 6>();
  InterruptCallback callback;
  uint8_t address;
  units::voltage::volt_t battery_voltage;
  float voltage;
  void Initialize()
  {
    // TODO - impliment initialize for state of charge
    i2c.Initialize();
    alert_pin.Initialize();
    address  = 0b0110110;
    voltage = 0;
  }

  void CalcState()
  {
    uint8_t address = 0b0110110;
    Max170343 * battery_sensor =
        new Max170343(i2c, alert_pin, callback, address);
    units::voltage::volt_t battery_voltage = battery_sensor->GetVoltage();
    double voltage                         = battery_voltage.to<double>();
    voltage = (voltage - 3) / (4.2 - 3);
    voltage = voltage * 100;
  }

  bool IsBatteryLow()
  {
    bool callback_was_called = true;
    if (voltage < 3.05)
    {
      sjsu::LogWarning("Cell Voltage below 3. Battery dangerously low!");
      return true;
    }
    else if (voltage < 3.25)
      InterruptCallback callback = [&callback_was_called]()
      { callback_was_called = true; };
     
    if (voltage < 3.05)
    {
      sjsu::LogWarning("Cell Voltage below 3. Battery dangerously low!");
      return true;
    }
    else if (voltage < 3.25)
    {
      sjsu::LogWarning("Cell Voltage below 3.25. Battery is low");
    }
     return false;
  }

  float GetStateOfCharge()
  {
    return voltage;
  }
};
}  // namespace sjsu::common