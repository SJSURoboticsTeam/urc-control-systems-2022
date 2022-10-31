#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class HandModes
    {
    public:
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
        static constexpr int kMinAngle = 88;
        static constexpr int kMaxAngle = 175;
        static constexpr int kMappedMinHandArgumentAngle=0;
        static constexpr int kMappedMaxHandArgumentAngle=100;
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
            commands.shoulder_angle = kCondensedShoulderAngle;
            commands.elbow_angle = kCondensedElbowAngle;
            commands.wrist_pitch_angle = kCondensedWristPitchAngle;
            commands.wrist_roll_angle = kCondensedWristYawAngle;
            return commands;
        }

        // TODO: come up with other possible modes

    private:
        static constexpr float kCondensedRotundaAngle = 0;
        static constexpr float kCondensedShoulderAngle = -18;
        static constexpr float kCondensedElbowAngle = 74;
        static constexpr float kCondensedWristPitchAngle = 0;
        static constexpr float kCondensedWristYawAngle = 0;
        static constexpr float kCondensedFingerAngle = 0;
        static constexpr int kMaxAngle = 75;
    };
}