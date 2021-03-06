#pragma once
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class CommandLerper
    {
    public:
        arm_arguments Lerp(arm_arguments commands)
        {
            last_lerped_command_.joint_args.elbow_angle = std::lerp(last_lerped_command_.joint_args.elbow_angle, commands.joint_args.elbow_angle, kSpeedLerp);
            last_lerped_command_.joint_args.rotunda_angle = std::lerp(last_lerped_command_.joint_args.rotunda_angle, commands.joint_args.rotunda_angle, kSpeedLerp);
            last_lerped_command_.joint_args.shoulder_angle = std::lerp(last_lerped_command_.joint_args.shoulder_angle, commands.joint_args.shoulder_angle, kSpeedLerp);
            last_lerped_command_.joint_args.wrist_yaw_angle = std::lerp(last_lerped_command_.joint_args.wrist_yaw_angle, commands.joint_args.wrist_yaw_angle, kSpeedLerp);
            last_lerped_command_.joint_args.wrist_pitch_angle = std::lerp(last_lerped_command_.joint_args.wrist_pitch_angle, commands.joint_args.wrist_pitch_angle, kSpeedLerp);
            commands.joint_args.elbow_angle = last_lerped_command_.joint_args.elbow_angle;
            commands.joint_args.rotunda_angle = last_lerped_command_.joint_args.rotunda_angle;
            commands.joint_args.shoulder_angle = last_lerped_command_.joint_args.shoulder_angle;
            commands.joint_args.wrist_pitch_angle = last_lerped_command_.joint_args.wrist_pitch_angle;
            commands.joint_args.wrist_yaw_angle = last_lerped_command_.joint_args.wrist_yaw_angle;
            return commands;
        }

    private:
        const double kSpeedLerp = .1;
        const double kAngleLerp = .20;
        arm_arguments last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}