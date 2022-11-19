#include <cstdio>
#include "../../common/serial.hpp"
#include "utility/log.hpp"
#include "devices/actuators/servo/servo.hpp"
#include "peripherals/lpc40xx/pwm.hpp"
#include "../../subsystem-arm/implementations/routers/rr9-router.hpp"

int main() {
    sjsu::LogInfo("Servo application starting...");
    // sjsu::lpc40xx::Pwm &pwm = sjsu::lpc40xx::GetPwm<1, 0>();

    sjsu::Servo servo(sjsu::lpc40xx::GetPwm<1, 0>());
    sjsu::LogInfo("Setting Servo pulse width bounds from 500us to 2500us.");
    // documentation says 1.5ms is neutral, but 1.5ms is 1500us
    servo.settings.min_pulse = 500us;
    servo.settings.max_pulse = 2500us;

    // Set the angle bounds of the servo to be 0 degrees and 180 degrees
    sjsu::LogInfo("Setting Servo angle bounds from 0 deg to 180 deg.");
    servo.settings.min_angle = 0_deg;
    servo.settings.max_angle = 200_deg;

    sjsu::arm::Rr9Router rr9_router(servo);
    rr9_router.Initialize();    
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
    std::string serial_input;
    sjsu::LogInfo("starting bla bla\n");
    while (1)
    {
        sjsu::LogInfo("looking for data!!!\n");
        sjsu::LogInfo("death 0\n");
        serial_input = serial.GetCommands();
        sjsu::LogInfo("death 1\n");
        if (!serial_input.compare("")) 
            rr9_router.SetAngle(stoi(serial_input));
        sjsu::LogInfo("death 2\n");
        sjsu::LogInfo("%s \n", serial_input);
        sjsu::Delay(1s);
    }

    
}