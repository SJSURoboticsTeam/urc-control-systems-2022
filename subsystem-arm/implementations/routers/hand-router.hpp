#pragma once
#include "utility/math/units.hpp"

#include "../pca9685.hpp"
#include "../../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class HandRouter
    {
    public:
        HandRouter(sjsu::Pca9685 &pca_module) : pca_module_(pca_module){};

        // Initialize
        void Initialize()
        {
            pca_module_.ModuleInitialize();
        }

        std::chrono::microseconds AngleToPulseWidth(int angle)
        {
            return std::chrono::microseconds(angle * (4096 / 360));
        }

        void MoveToAngle(hand_arguments hand_arguments)
        {
            pca_module_.setPulseWidth(0, AngleToPulseWidth(hand_arguments.pinky_argument));
            pca_module_.setPulseWidth(1, AngleToPulseWidth(hand_arguments.ring_argument));
            pca_module_.setPulseWidth(2, AngleToPulseWidth(hand_arguments.middle_argument));
            pca_module_.setPulseWidth(3, AngleToPulseWidth(hand_arguments.index_argument));
            pca_module_.setPulseWidth(4, AngleToPulseWidth(hand_arguments.thumb_argument));
        }

    private:
        // sjsu::arm::arm_arguments arguments_;
        // hand_arguments hand_arguments_;
        sjsu::Pca9685 &pca_module_;
    };
}
