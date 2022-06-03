#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class ArmModes
    {
        public:
            static constexpr float kCondRotundaAngle = 0;
            static constexpr float kCondShoulderAngle = -18;
            static constexpr float kCondElbowAngle = 74;
            static constexpr float kCondWristPitchAngle = 0;
            static constexpr float kCondWristYawAngle = 0;
            static constexpr float kCondFingerAngle = 0;

            static arm_arguments SimulataneousMode(arm_commands commands)
            {}

            static arm_arguments CondensedMode(arm_commands commands)
            {
                arm_arguments temp;
                temp.rotunda_angle = kCondRotundaAngle;
                temp.shoulder_angle = kCondShoulderAngle;
                temp.elbow_angle = kCondElbowAngle;
                temp.wrist_pitch_angle = kCondWristPitchAngle;
                temp.wrist_yaw_angle = kCondWristYawAngle;

                return temp;
            }

            
            //TODO: come up with other possible modes
    };
}