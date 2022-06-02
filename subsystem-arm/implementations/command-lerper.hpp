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
            return commands;
        }

    private:
        const double kSpeedLerp = .1;
        const double kAngleLerp = .20;
        arm_commands last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}