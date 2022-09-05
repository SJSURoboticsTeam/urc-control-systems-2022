#pragma once
#include "../dto/drive-dto.hpp"
#include "../common/heartbeat.hpp"

namespace sjsu::drive
{
    class RulesEngine
    {
    public:
        static constexpr int kMaxSpeed = 100;
        drive_commands ValidateCommands(drive_commands commands)
        {
            // if(!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
            // {
            //     commands.speed = 0;
            //     //sjsu::LogInfo("Overriding speed");
            //     return commands;
            // }
            if (!commands.is_operational)
            {
                commands.speed = 0;
                //sjsu::LogInfo("Overriding speed");
                return commands;
            }
            if(!commands.is_operational)
            {
                commands.speed = 0;
                //sjsu::LogInfo("System is not operational... overriding speed");
            }
            if(commands.speed > kMaxSpeed || commands.speed < -kMaxSpeed)
            {
                commands.speed = std::clamp(commands.speed, -kMaxSpeed, kMaxSpeed);
                //sjsu::LogInfo("Specified speed is too fast... clamping speed");
            }
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}