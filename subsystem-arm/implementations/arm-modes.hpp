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

            static arm_arguments SimulataneousMode(arm_commands commands)
            {}

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