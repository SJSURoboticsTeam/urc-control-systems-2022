#pragma once
#include "peripherals/lpc40xx/i2c.hpp"
#include "../implementations/pca9685.hpp" 
#include "hand-router.hpp"

namespace sjsu::arm
{
    class HandModes
    {
    public:

        static hand_arguments CloseMode(hand_arguments arguments)
        {
            arguments.pinky_angle = min_angle_;
            arguments.ring_angle = min_angle_;
            arguments.middle_angle = min_angle_;
            arguments.index_angle = min_angle_;
            arguments.thumb_angle = min_angle_;
            return arguments;
        }

        static hand_arguments OpenMode(hand_arguments arguments)
        {
            arguments.pinky_angle = max_angle_;
            arguments.ring_angle = max_angle_;
            arguments.middle_angle = max_angle_;
            arguments.index_angle = max_angle_;
            arguments.thumb_angle = max_angle_;
            return arguments;
        }

        static hand_arguments ManualMode(hand_arguments arguments)
        {
            return arguments;
        }

        static hand_arguments ClawMode(hand_arguments arguments)
        {

        }

        static hand_arguments RestMode(hand_arguments arguments)
        {

        }


    private:
        static constexpr int min_angle_     = 30;
        static constexpr int neutral_angle_ = 90;
        static constexpr int max_angle_     = 180;
    };
}