#pragma once
#include "dto/hand-dto.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "pca9685.hpp"

namespace sjsu::arm
{
    class HandModes
    {
    public:

        static hand_arguments CloseHand(hand_arguments arguments_)
        {
            arguments_.pinky_angle = min_angle_;
            arguments_.ring_angle = min_angle_;
            arguments_.middle_angle = min_angle_;
            arguments_.index_angle = min_angle_;
            arguments_.thumb_angle = min_angle_;
            return arguments_;
        }

        static hand_arguments OpenHand(hand_arguments arguments_)
        {
            arguments_.pinky_angle = max_angle_;
            arguments_.ring_angle = max_angle_;
            arguments_.middle_angle = max_angle_;
            arguments_.index_angle = max_angle_;
            arguments_.thumb_angle = max_angle_;
            return arguments_;
        }

        static hand_arguments PointHand(hand_arguments arguments_)
        {
            arguments_.pinky_angle = min_angle_;
            arguments_.ring_angle = min_angle_;
            arguments_.middle_angle = min_angle_;
            arguments_.index_angle = neutral_angle_;
            arguments_.thumb_angle = max_angle_;
            return arguments_;
        }

    private:
        int min_angle_     = 30;
        int neutral_angle_ = 90;
        int max_angle_     = 180;
    };
}