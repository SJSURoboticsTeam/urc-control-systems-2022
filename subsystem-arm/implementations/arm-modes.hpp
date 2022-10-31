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

        static joint_arguments CondensedMode(joint_arguments commands)
        {
            commands.rotunda_angle = kCondensedRotundaAngle;
            sjsu::Delay(3s);
            commands.shoulder_angle = kCondensedShoulderAngle;
            commands.elbow_angle = kCondensedElbowAngle;
            commands.wrist_pitch_angle = kCondensedWristPitchAngle;
            commands.wrist_roll_angle = kCondensedWristRollAngle;
            return commands;
        }

        // TODO: come up with other possible modes

    private:
        static constexpr float kCondensedRotundaAngle = 0;
        static constexpr float kCondensedShoulderAngle = -18;
        static constexpr float kCondensedElbowAngle = 74;
        static constexpr float kCondensedWristPitchAngle = 0;
        static constexpr float kCondensedWristRollAngle = 0;
        static constexpr float kCondensedFingerAngle = 0;
        static constexpr int kMaxAngle = 75;
    };
}