#pragma once

#include "../dto/drive-dto.hpp"
#include "../common/heartbeat.hpp"

namespace sjsu::drive
{
    class RulesEngine
    {
    public:
        static constexpr int kMaxSpeed = 100;
        static constexpr int kMaxAngle = 12;

        drive_commands ValidateCommands(drive_commands commands)
        {
            // if(!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
            // {
            //     commands.speed = 0;
            //     return commands;
            // }

            if (commands.mode == 'D')
            {
                commands.angle = std::clamp(commands.angle, -kMaxAngle, kMaxAngle);
            }

            if (!commands.is_operational)
            {
                commands.speed = 0;
                return commands;
            }

            commands.speed = std::clamp(commands.speed, -kMaxSpeed, kMaxSpeed);

            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}