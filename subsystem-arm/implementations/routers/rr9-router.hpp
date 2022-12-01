#pragma once
#include "utility/math/units.hpp"

#include "devices/actuators/servo/servo.hpp"
#include "../../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class Rr9Router
    {
    public:
        // Rr9Router(sjsu::Pca9685 &pca_module) : pca_module_(pca_module){};
        Rr9Router(sjsu::Servo &servo) : servo_(servo){};

        /*
        instance variables
        Servo = new myServo;

        Rr9Router(Servo servo) {
            this.myServo = servo;
        }
        */

        // Initialize
        void Initialize()
        {
            servo_.settings.min_pulse = 500us;
            servo_.settings.max_pulse = 2500us; 
            servo_.settings.min_angle = 0_deg;
            servo_.settings.max_angle = 200_deg;
            servo_.Initialize();
        }

        void SetRr9Angle(int angle) {
            
            servo_.SetAngle(units::angle::degree_t(static_cast<float>(angle)));
        }

        rr9_arguments SetRr9Arguments(rr9_arguments rr9_args, char mode)
        {
            if(mode == 'R') {
                SetRr9Angle(rr9_args.angle);
            }
            return rr9_args;
        }


    private:
        // sjsu::arm::arm_arguments arguments_;
        // hand_arguments hand_arguments_;
        sjsu::Servo &servo_;
    };
}
