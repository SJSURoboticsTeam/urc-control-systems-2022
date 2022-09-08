#pragma once
#include "utility/math/units.hpp"
#include "../arm-dto.hpp"
#include "../pca9685.hpp"

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

        void MoveToAngle(hand_arguments Hand_Arguments)
        {
            pca_module_.setPulseWidth(0, AngleToPulseWidth(Hand_Arguments.pinky_angle));
            pca_module_.setPulseWidth(1, AngleToPulseWidth(Hand_Arguments.ring_angle));
            pca_module_.setPulseWidth(2, AngleToPulseWidth(Hand_Arguments.middle_angle));
            pca_module_.setPulseWidth(3, AngleToPulseWidth(Hand_Arguments.index_angle));
            pca_module_.setPulseWidth(4, AngleToPulseWidth(Hand_Arguments.thumb_angle));
        }

    private:
        // sjsu::arm::arm_arguments arguments_;
        hand_arguments hand_arguments_;
        sjsu::Pca9685 &pca_module_;
    };
}
