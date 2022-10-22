#pragma once
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class CommandLerper
    {
    public:
        arm_arguments Lerp(arm_arguments commands)
        {
            last_lerped_command_.joint_args.speed = std::lerp(last_lerped_command_.joint_args.speed, commands.joint_args.speed, kSpeedLerp);
            
            return commands;
        }

    private:
        const double kSpeedLerp = .1;
        const double kAngleLerp = .20;
        arm_arguments last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}