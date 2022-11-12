#include <array>
#include <cstdint>

#include "peripherals/lpc40xx/pwm.hpp"
#include "devices/actuators/servo/servo.hpp"
#include "utility/log.hpp"
#include "utility/time/time.hpp"
#include "utility/log.hpp"
#include "peripherals/lpc40xx/uart.hpp"
#include "../../common/serial.hpp"
#include "peripherals/lpc40xx/adc.hpp"

int main()
{
    sjsu::LogInfo("Servo application starting...");
    sjsu::lpc40xx::Pwm &pwm = sjsu::lpc40xx::GetPwm<1, 0>();
    sjsu::LogInfo("ADC channel 5 is connected to pin P1.31");
    sjsu::lpc40xx::Adc & adc5 = sjsu::lpc40xx::GetAdc<5>();

    sjsu::Servo servo(pwm);
    sjsu::LogInfo("Setting Servo pulse width bounds from 500us to 2500us.");
    // documentation says 1.5ms is neutral, but 1.5ms is 1500us
    servo.settings.min_pulse = 500us;
    servo.settings.max_pulse = 2500us;

    // Set the angle bounds of the servo to be 0 degrees and 180 degrees
    sjsu::LogInfo("Setting Servo angle bounds from 0 deg to 180 deg.");
    servo.settings.min_angle = 0_deg;
    servo.settings.max_angle = 200_deg;

    sjsu::LogInfo("Initalizing Servo");
    servo.Initialize();

    // Initializing pin 31 for potentiometer
    adc5.Initialize();

    sjsu::LogInfo("Serial Testing Starting...");
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
    
    while (true)
    {
        uint32_t digital_value = adc5.Read();

        sjsu::LogInfo("ADC5 = %04lu",
                digital_value);

        float servo_angle =
                sjsu::Map(digital_value, 0, adc5.GetMaximumValue(), 0, 170);

        sjsu::LogInfo("%f\n", servo_angle);

        servo.SetAngle(units::angle::degree_t(servo_angle));
    }
    return 0;
}
