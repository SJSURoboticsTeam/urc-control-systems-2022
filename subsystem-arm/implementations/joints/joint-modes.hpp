#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
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
            commands.wrist_yaw_angle = kCondensedWristYawAngle;
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