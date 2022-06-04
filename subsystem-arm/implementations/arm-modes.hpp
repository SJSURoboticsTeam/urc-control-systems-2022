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
            
        //TODO: come up with other possible modes
        static arm_arguments SimulataneousMode(arm_commands commands)
        {
            arm_arguments temp;
            temp.rotunda_angle = AnglesConvert(commands.rotunda_angle);
            temp.shoulder_angle = AnglesConvert(commands.shoulder_angle);
            temp.elbow_angle = AnglesConvert(commands.elbow_angle);
            temp.wrist_pitch_angle = AnglesConvert(commands.wrist_pitch_angle);
            temp.wrist_yaw_angle = AnglesConvert(commands.wrist_yaw_angle);
            temp.finger_angle = AnglesConvert(commands.finger_angle);
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
        private:
        int AnglesConvert(int angle){
            int temp;
            temp = angle %360;
            if(temp>180){
                temp=-360;
            }
            return temp;
        }
    };
}