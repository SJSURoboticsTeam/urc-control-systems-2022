#pragma once

#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class CommandLerper
    {
    public:
        drive_commands Lerp(drive_commands commands)
        {
            last_lerped_command_.speed = static_cast<int>(std::lerp(static_cast<float>(last_lerped_command_.speed), static_cast<float>(commands.speed), kSpeedLerp)); //get second eyes on this one
            last_lerped_command_.angle = static_cast<int>(std::lerp(static_cast<float>(last_lerped_command_.angle), static_cast<float>(commands.angle), kAngleLerp));
            commands.speed = last_lerped_command_.speed;
            commands.angle = last_lerped_command_.angle;
            return commands;
        }

    private:
        const float kSpeedLerp = 0.4f;
        const float kAngleLerp = 0.6f;
        drive_commands last_lerped_command_{}; // don't touch mode or wheel orientation logic
    };
}