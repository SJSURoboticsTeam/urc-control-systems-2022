#pragma once

#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class CommandLerper
    {
    public:
        drive_commands Lerp(drive_commands commands)
        {
            last_lerped_speed_ = static_cast<int>(std::lerp(static_cast<float>(last_lerped_speed_), static_cast<float>(commands.speed), kSpeedLerp));
            commands.speed = last_lerped_speed_;
            return commands;
        }

    private:
        const float kSpeedLerp = 0.4f;
        int last_lerped_speed_ = 0;
    };
}