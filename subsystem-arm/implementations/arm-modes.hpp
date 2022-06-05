#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class ArmModes
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
        static arm_arguments SimulataneousMode(arm_commands commands)
        {
            arm_arguments temp;
            temp.rotunda_angle = static_cast<int>(std::clamp(commands.rotunda_angle, -kMaxAngle, kMaxAngle));
            temp.shoulder_angle = static_cast<int>(std::clamp(commands.shoulder_angle, -kMaxAngle, kMaxAngle));
            temp.elbow_angle = static_cast<int>(std::clamp(commands.elbow_angle, -kMaxAngle, kMaxAngle));
            temp.wrist_pitch_angle = static_cast<int>(std::clamp(commands.wrist_pitch_angle, -kMaxAngle, kMaxAngle));
            temp.wrist_yaw_angle = static_cast<int>(std::clamp(commands.wrist_yaw_angle, -kMaxAngle, kMaxAngle));
            return temp;
        }

        static arm_arguments CondensedMode(arm_commands commands)
        {
            arm_arguments temp;
            temp.rotunda_angle = kCondensedRotundaAngle;
            temp.shoulder_angle = kCondensedShoulderAngle;
            temp.elbow_angle = kCondensedElbowAngle;
            temp.wrist_pitch_angle = kCondensedWristPitchAngle;
            temp.wrist_yaw_angle = kCondensedWristYawAngle;

            return temp;
        }
        //TODO: come up with other possible modes
    };
}