#pragma once
#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class CommandLerper
    {
    public:
        arm_commands Lerp(arm_commands commands)
        {
            //TODO
            return commands;
        }

    private:
        const double kSpeedLerp = .1;
        const double kAngleLerp = .20;
        arm_commands last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}