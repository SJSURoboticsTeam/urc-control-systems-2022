#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class JointModes
    {
    public:
        static arm_arguments SimulataneousMode(arm_arguments commands)
        {
            return commands;
        }

        static arm_arguments CondensedMode(arm_arguments commands)
        {
            commands.joint_args.rotunda_angle = kCondensedRotundaAngle;
            commands.joint_args.shoulder_angle = kCondensedShoulderAngle;
            commands.joint_args.elbow_angle = kCondensedElbowAngle;
            commands.joint_args.wrist_pitch_angle = kCondensedWristPitchAngle;
            commands.joint_args.wrist_yaw_angle = kCondensedWristYawAngle;
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