#pragma once
#include "utility/math/units.hpp"
#include "devices/actuators/servo/servo.hpp"
#include "../pca9685.hpp"
#include "../../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class HandRouter
    {
    public:
        HandRouter(sjsu::Pca9685 *pca_module) : pca_module_(pca_module) {
            pca_module_->ModuleInitialize();
        }

        // rr9 servo ctor
        HandRouter(sjsu::Servo *servo) : servo_(servo){
            servo_->settings.min_pulse = 500us;
            servo_->settings.max_pulse = 2500us;
            servo_->settings.min_angle = 0_deg;
            servo_->settings.max_angle = 200_deg;
            servo_->Initialize();
        }

        std::chrono::microseconds AngleToPulseWidth(int angle)
        {
            return std::chrono::microseconds(angle * (4096 / 360));
        }

        hand_arguments SetHandArguments(hand_arguments hand_arguments, char mode)
        {
            if(mode == 'H') {
                pca_module_->setPulseWidth(0, AngleToPulseWidth(hand_arguments.pinky_angle));
                pca_module_->setPulseWidth(1, AngleToPulseWidth(hand_arguments.ring_angle));
                pca_module_->setPulseWidth(2, AngleToPulseWidth(hand_arguments.middle_angle));
                pca_module_->setPulseWidth(3, AngleToPulseWidth(hand_arguments.index_angle));
                pca_module_->setPulseWidth(4, AngleToPulseWidth(hand_arguments.thumb_angle));
            }
            else if(mode == 'R') {
                // do logic for RR9 moving here
                servo_->SetAngle(units::angle::degree_t(static_cast<float>(hand_arguments.pinky_angle)));
            }
            return hand_arguments;
        }



    private:
        // sjsu::arm::arm_arguments arguments_;
        // hand_arguments hand_arguments_;
        sjsu::Pca9685 *pca_module_;
        sjsu::Servo *servo_;
        char mode_;
    };
}
