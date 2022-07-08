#pragma once
//#include "dto/hand-dto.hpp"
#include "utility/math/units.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "../implementations/pca9685.hpp"

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

        void MoveToAngle(hand_arguments)
        {
            pca_module_.setPulseWidth(0, AngleToPulseWidth(hand_arguments_.pinky_angle));
            pca_module_.setPulseWidth(1, AngleToPulseWidth(hand_arguments_.ring_angle));
            pca_module_.setPulseWidth(2, AngleToPulseWidth(hand_arguments_.middle_angle));
            pca_module_.setPulseWidth(3, AngleToPulseWidth(hand_arguments_.index_angle));
            pca_module_.setPulseWidth(4, AngleToPulseWidth(hand_arguments_.thumb_angle));
        }
    private:
        //sjsu::arm::arm_arguments arguments_;
        hand_arguments hand_arguments_;
        sjsu::Pca9685 &pca_module_;
    };
}
