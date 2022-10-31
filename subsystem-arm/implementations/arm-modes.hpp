#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class ArmMode
    {
        public:
            static void JointMode(mc_commands commands, arm_arguments &args)
            {
                args.joint_args.rotunda_angle = commands.first_angle;
                args.joint_args.shoulder_angle = commands.second_angle;
                args.joint_args.elbow_angle = commands.third_angle;
                args.joint_args.wrist_pitch_angle = commands.fourth_angle;
                args.joint_args.wrist_roll_angle = commands.fifth_angle;
            }

            static void HandMode(mc_commands commands, arm_arguments &args)
            {
                args.hand_args.pinky_angle = commands.first_angle;
                args.hand_args.ring_angle = commands.second_angle;
                args.hand_args.middle_angle = commands.third_angle;
                args.hand_args.index_angle = commands.fourth_angle;
                args.hand_args.thumb_angle = commands.fifth_angle;
            }

            static void RRNineMode(mc_commands commands, arm_arguments &args) 
            {
                // put logic here
            }
        private:

    };
}