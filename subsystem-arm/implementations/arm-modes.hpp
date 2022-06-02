#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsus::arm
{
    class ArmModes
    {
        public:

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