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
            temp.rotunda_angle = anglesconvert(commands.rotunda_angle);
            temp.shoulder_angle = anglesconvert(commands.shoulder_angle);
            temp.elbow_angle = anglesconvert(commands.elbow_angle);
            temp.wrist_pitch_angle = anglesconvert(commands.wrist_pitch_angle);
            temp.wrist_yaw_angle = anglesconvert(commands.wrist_yaw_angle);
            temp.finger_angle = anglesconvert(commands.finger_angle);
            return{}
        }

        static arm_arguments CondensedMode(arm_commands commands)
        {

        }
        //TODO: come up with other possible modes
        private:
        int anglesconvert(int a){
            int temp;
            temp = a%360;
            if(temp>180){
                temp=-360;
            }
            return temp;
        }
    };
}