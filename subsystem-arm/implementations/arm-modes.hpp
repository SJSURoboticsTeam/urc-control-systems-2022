#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class HandModes
    {
    public:
        // Closes the hand to the minimum angle
        static hand_arguments CloseMode(hand_arguments arguments)
        {
            arguments.pinky_angle = min_angle_;
            arguments.ring_angle = min_angle_;
            arguments.middle_angle = min_angle_;
            arguments.index_angle = min_angle_;
            arguments.thumb_angle = min_angle_;
            return arguments;
        }
        // Opens the hand to the maximum angle
        static hand_arguments OpenMode(hand_arguments arguments)
        {
            arguments.pinky_angle = max_angle_;
            arguments.ring_angle = max_angle_;
            arguments.middle_angle = max_angle_;
            arguments.index_angle = max_angle_;
            arguments.thumb_angle = max_angle_;
            return arguments;
        }
        // Sets angle of each finger according to what mission control sends to each individual finger.
        static hand_arguments IndividualMode(hand_arguments arguments)
        {
            return arguments;
        }
        // Sets angle of all fingers according to what mission control sends to finger_angle.
        static hand_arguments SimultaneousMode(hand_arguments arguments)
        {
            arguments.pinky_angle = arguments.index_angle;
            arguments.ring_angle = arguments.index_angle;
            arguments.middle_angle = arguments.index_angle;
            arguments.index_angle = arguments.index_angle;
            arguments.thumb_angle = arguments.index_angle;
            return arguments;
        }

    private:
        static constexpr int min_angle_ = 88;
        static constexpr int max_angle_ = 175;
    };

    class JointModes
    {
    public:
        static joint_arguments SimultaneousMode(joint_arguments commands)
        {
            return commands;
        }

    private:

        static wrist_arguments CalcWristSpeed()
        {
            
        }
        static constexpr int kMaxAngle = 75;
    };
}