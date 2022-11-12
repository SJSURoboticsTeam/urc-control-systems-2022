#pragma once
#include "utility/math/units.hpp"

#include "../pca9685.hpp"
#include "../../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class HandRouter
    {
    public:
        HandRouter(sjsu::Pca9685 &pca_module, sjsu::Servo &servo) : pca_module_(pca_module),servo_(servo){};

        // Initialize
        void Initialize()
        {
            pca_module_.ModuleInitialize();
            servo_.Initialize();

        }
        

        std::chrono::microseconds AngleToPulseWidth(int angle)
        {
            return std::chrono::microseconds(angle * (4096 / 360));
        }

        hand_arguments SetArguments(hand_arguments hand_arguments, char mode)
        {
            if(mode == 'H') {
                pca_module_.setPulseWidth(0, AngleToPulseWidth(hand_arguments.pinky_angle));
                pca_module_.setPulseWidth(1, AngleToPulseWidth(hand_arguments.ring_angle));
                pca_module_.setPulseWidth(2, AngleToPulseWidth(hand_arguments.middle_angle));
                pca_module_.setPulseWidth(3, AngleToPulseWidth(hand_arguments.index_angle));
                pca_module_.setPulseWidth(4, AngleToPulseWidth(hand_arguments.thumb_angle));
            }
            else if(mode == 'R') {
                // do logic for RR9 moving here
                int pot_max = 4095;
                servo_.SetAngle(units::angle::degree_t(sjsu::Map(hand_arguments.pinky_angle, 0, pot_max, 0, 170)));
                
            }
            return hand_arguments;
        }
        



    private:
        // sjsu::arm::arm_arguments arguments_;
        // hand_arguments hand_arguments_;
        sjsu::Pca9685 &pca_module_;
        sjsu::Servo &servo_;
    };
}
