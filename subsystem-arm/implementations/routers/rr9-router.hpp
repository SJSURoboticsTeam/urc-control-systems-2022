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
            servo_.Initialize();
        }

        void SetAngle(int angle) {
            servo_.SetAngle(units::angle::degree_t(angle));
        }

    private:
        // sjsu::arm::arm_arguments arguments_;
        // hand_arguments hand_arguments_;
        sjsu::Servo &servo_;
    };
}
