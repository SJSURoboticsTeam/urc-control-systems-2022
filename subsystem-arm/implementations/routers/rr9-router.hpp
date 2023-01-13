#pragma once
#include "utility/math/units.hpp"
#include "devices/actuators/servo/servo.hpp"
#include "../pca9685.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class RR9Router
    {
    public:

        // rr9 servo ctor
        RR9Router(sjsu::Servo *servo) : servo_(servo)
        {
            servo_->settings.min_pulse = 500us;
            servo_->settings.max_pulse = 2500us;
            servo_->settings.min_angle = 0_deg;
            servo_->settings.max_angle = 200_deg;
            servo_->Initialize();
        }

        mc_commands SetRR9Arguments(mc_commands args)
        {
            // do logic for RR9 moving here
            servo_->SetAngle(units::angle::degree_t(static_cast<float>(args.rr9_angle)));
            return args;
        }

    private:
        sjsu::Servo *servo_;
    };
}
