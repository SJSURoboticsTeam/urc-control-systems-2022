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

            if (commands.mode == 'D')
            {
                // sjsu::LogInfo("Specified angle is too large... clamping angle");
                commands.angle = std::clamp(commands.angle, -kMaxAngle, kMaxAngle);
            }
            if(!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
            {
                sjsu::LogInfo("Heartbeat is out of sync... setting speed to 0");
                commands.speed = 0;
                return commands;
            }
            else
            {
                sjsu::LogInfo("Heartbeat is sync");
            }
            if (!commands.is_operational)
            {
                //sjsu::LogInfo("System is not operational... setting speed to 0");
                commands.speed = 0;
                return commands;
            }
            if (commands.speed > kMaxSpeed || commands.speed < -kMaxSpeed)
            {
                // sjsu::LogInfo("Specified speed is too fast... clamping speed");
                commands.speed = std::clamp(commands.speed, -kMaxSpeed, kMaxSpeed);
            }

            return commands;
        }

    drive_commands HeartbeatRoverStatus(drive_commands commands)
    {
        heartbeat_.IncrementHeartbeatCount();

        sjsu::LogInfo("Rover Heartbeat: %d", heartbeat_.GetHeartbeatCount());

        return commands;
    }
    private:
        sjsu::common::Heartbeat heartbeat_;

    
    };
}