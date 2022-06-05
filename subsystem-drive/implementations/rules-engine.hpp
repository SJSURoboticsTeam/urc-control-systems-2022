#pragma once
#include "../dto/drive-dto.hpp"
#include "../common/heartbeat.hpp"

namespace sjsu::drive
{
    class RulesEngine
    {
        public:
        drive_commands Check(drive_commands commands)
        {
            if(heartbeat.IsSyncedWithMissionControl(commands.heartbeat_count))
            {
                commands.speed = 0;
                sjsu::LogInfo("Overriding speed");
                return commands;
            }
            if(!commands.is_operational)
            {
                commands.speed = 0;
                sjsu::LogInfo("System is not operational... overriding speed");
            }
            if(commands.speed > 100)
            {
                commands.speed = std::clamp(commands.speed, -max_speed, max_speed);
                sjsu::LogInfo("Specified speed is too fast... clamping speed");
            }
            heartbeat.IncrementHeartbeatCount();
            return commands;
        }

        private:
        sjsu::common::Heartbeat heartbeat;
        int max_speed = 100;
    };
}