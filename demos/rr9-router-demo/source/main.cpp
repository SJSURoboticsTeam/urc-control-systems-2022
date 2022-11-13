#include <cstdio>

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
    while (1)
    {
        rr9_router.SetAngle(0);
        sjsu::Delay(1s);
        rr9_router.SetAngle(90);
        sjsu::Delay(1s);
    }

    
}