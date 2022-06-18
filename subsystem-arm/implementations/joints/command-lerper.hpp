#pragma once
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class CommandLerper
    {
    public:
        arm_arguments Lerp(arm_arguments commands)
        {
            last_lerped_command_.elbow_angle = std::lerp(last_lerped_command_.elbow_angle, commands.elbow_angle, kSpeedLerp);
            last_lerped_command_.rotunda_angle = std::lerp(last_lerped_command_.rotunda_angle, commands.rotunda_angle, kSpeedLerp);
            last_lerped_command_.shoulder_angle = std::lerp(last_lerped_command_.shoulder_angle, commands.shoulder_angle, kSpeedLerp);
            last_lerped_command_.wrist_yaw_angle = std::lerp(last_lerped_command_.wrist_yaw_angle, commands.wrist_yaw_angle, kSpeedLerp);
            last_lerped_command_.wrist_pitch_angle = std::lerp(last_lerped_command_.wrist_pitch_angle, commands.wrist_pitch_angle, kSpeedLerp);
            commands.joint_arguments.elbow_angle = last_lerped_command_.joint_arguments.elbow_angle;
            commands.rotunda_angle = last_lerped_command_.rotunda_angle;
            commands.shoulder_angle = last_lerped_command_.shoulder_angle;
            commands.wrist_pitch_angle = last_lerped_command_.wrist_pitch_angle;
            commands.wrist_yaw_angle = last_lerped_command_.wrist_yaw_angle;
            return commands;
        }

    private:
        const double kSpeedLerp = .1;
        const double kAngleLerp = .20;
        arm_arguments last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}