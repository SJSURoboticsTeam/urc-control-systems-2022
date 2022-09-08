#pragma once

#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class CommandLerper
    {
    public:
        drive_commands Lerp(drive_commands commands)
        {
            last_lerped_command_.speed = std::lerp(last_lerped_command_.speed, commands.speed, kSpeedLerp);
            last_lerped_command_.angle = std::lerp(last_lerped_command_.angle, commands.angle, kAngleLerp);
            commands.speed = last_lerped_command_.speed;
            commands.angle = last_lerped_command_.angle;
            return commands;
        }

    private:
        const double kSpeedLerp = .4;
        const double kAngleLerp = .6;
        drive_commands last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}