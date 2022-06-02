#pragma once
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class CommandLerper
    {
    public:
        arm_commands Lerp(arm_commands commands)
        {
            // TODO
            
            last_lerped_command_.elbow_angle = std::lerp(last_lerped_command_.elbow_angle, commands.elbow_angle, kSpeedLerp);
            commands = last_lerped_command_;
            return commands;
        }

    private:
        const double kSpeedLerp = .1;
        const double kAngleLerp = .20;
        arm_commands last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}