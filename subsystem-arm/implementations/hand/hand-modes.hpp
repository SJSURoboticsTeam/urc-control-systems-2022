#pragma once
#include "dto/hand-dto.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "pca9685.hpp" 
#include "hand-router.hpp"

namespace sjsu::arm
{
    class HandModes
    {
    public:

        static hand_arguments CloseHand(hand_arguments arguments)
        {
            arguments.pinky_angle = min_angle_;
            arguments.ring_angle = min_angle_;
            arguments.middle_angle = min_angle_;
            arguments.index_angle = min_angle_;
            arguments.thumb_angle = min_angle_;
            return arguments;
        }

        static hand_arguments OpenHand(hand_arguments arguments)
        {
            arguments.pinky_angle = max_angle_;
            arguments.ring_angle = max_angle_;
            arguments.middle_angle = max_angle_;
            arguments.index_angle = max_angle_;
            arguments.thumb_angle = max_angle_;
            return arguments;
        }

        static hand_arguments PointHand(hand_arguments arguments)
        {
            arguments.pinky_angle = min_angle_;
            arguments.ring_angle = min_angle_;
            arguments.middle_angle = min_angle_;
            arguments.index_angle = neutral_angle_;
            arguments.thumb_angle = max_angle_;
            return arguments;
        }

        static hand_arguments ManualHand(hand_arguments arguments)
        {
            return arguments;
        }

        static hand_arguments ClawHand(hand_arguments arguments)
        {

        }


    private:
        int min_angle_     = 30;
        int neutral_angle_ = 90;
        int max_angle_     = 180;
    };
}