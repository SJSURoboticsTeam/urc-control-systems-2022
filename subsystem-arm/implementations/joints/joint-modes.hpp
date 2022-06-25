#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class JointModes
    {
        public:
            static constexpr float kCondensedRotundaAngle = 0;
            static constexpr float kCondensedShoulderAngle = -18;
            static constexpr float kCondensedElbowAngle = 74;
            static constexpr float kCondensedWristPitchAngle = 0;
            static constexpr float kCondensedWristYawAngle = 0;
            static constexpr float kCondensedFingerAngle = 0;
            static constexpr int kMaxAngle = 180;
            
        //TODO: come up with other possible modes
        static arm_arguments SimulataneousMode(arm_arguments commands)
        {
            arm_arguments temp;
            temp.joint_args.rotunda_angle = static_cast<int>(std::clamp(commands.joint_args.rotunda_angle, -kMaxAngle, kMaxAngle));
            temp.joint_args.shoulder_angle = static_cast<int>(std::clamp(commands.joint_args.shoulder_angle, -kMaxAngle, kMaxAngle));
            temp.joint_args.elbow_angle = static_cast<int>(std::clamp(commands.joint_args.elbow_angle, -kMaxAngle, kMaxAngle));
            temp.joint_args.wrist_pitch_angle = static_cast<int>(std::clamp(commands.joint_args.wrist_pitch_angle, -kMaxAngle, kMaxAngle));
            temp.joint_args.wrist_yaw_angle = static_cast<int>(std::clamp(commands.joint_args.wrist_yaw_angle, -kMaxAngle, kMaxAngle));
            return temp;
        }

        static arm_arguments CondensedMode(arm_arguments commands)
        {
            arm_arguments temp;
            temp.joint_args.rotunda_angle = kCondensedRotundaAngle;
            temp.joint_args.shoulder_angle = kCondensedShoulderAngle;
            temp.joint_args.elbow_angle = kCondensedElbowAngle;
            temp.joint_args.wrist_pitch_angle = kCondensedWristPitchAngle;
            temp.joint_args.wrist_yaw_angle = kCondensedWristYawAngle;

            return temp;
        }
        //TODO: come up with other possible modes
    };
}