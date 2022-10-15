#include <cstdint>

#include "peripherals/lpc40xx/pwm.hpp"
#include "devices/actuators/servo/servo.hpp"
#include "utility/log.hpp"
#include "utility/time/time.hpp"
#include "utility/log.hpp"
#include "peripherals/lpc40xx/uart.hpp"
#include "../../common/serial.hpp"

int main()
{
    sjsu::LogInfo("Servo application starting...");
    sjsu::lpc40xx::Pwm &pwm = sjsu::lpc40xx::GetPwm<1, 0>();
    sjsu::Servo servo(pwm);
    sjsu::LogInfo("Setting Servo pulse width bounds from 500us to 2500us.");
    // documentation says 1.5ms is neutral, but 1.5ms is 1500us
    servo.settings.min_pulse = 1300us;
    servo.settings.max_pulse = 1700us;

    // Set the angle bounds of the servo to be 0 degrees and 180 degrees
    sjsu::LogInfo("Setting Servo angle bounds from 0 deg to 180 deg.");
    servo.settings.min_angle = 0_deg;
    servo.settings.max_angle = 180_deg;

    sjsu::LogInfo("Initalizing Servo");
    servo.Initialize();

    sjsu::LogInfo("Serial Testing Starting...");
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
    int entered_angle = 0;

    while (true)
    {
        std::string response = serial.GetCommands();
        if (response != "")
        {
            printf("Received: %s\n", response.c_str());
            entered_angle = std::stoi(response);
        }
        units::angle::degree_t desired_angle(entered_angle);
        sjsu::LogInfo("Setting servo to %d degrees", entered_angle);
        servo.SetAngle(desired_angle);
        sjsu::Delay(1s);

        // this is more realistic
        // for (units::angle::degree_t servo_angle = 0_deg; servo_angle < 180_deg; servo_angle++)
        // {
        //     sjsu::LogInfo("Setting servo to %f degrees", servo_angle.to<double>());
        //     servo.SetAngle(servo_angle);
        //     sjsu::Delay(27ms);
        // }

        // not sure why they did this but it was in the demo
        // for (std::chrono::microseconds pulse_width = 1700us; pulse_width > 1300us; pulse_width--)
        // {
        //     servo.SetPulseWidthInMicroseconds(pulse_width);
        //     float angle = static_cast<float>(pulse_width.count() - 500) / 10.0f;
        //     sjsu::LogInfo("%f", angle);
        //     sjsu::Delay(10ms);
        // }
    }
    return 0;
}