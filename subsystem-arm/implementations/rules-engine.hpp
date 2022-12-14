#pragma once
#include "utility/log.hpp"

#include "../dto/arm-dto.hpp"
#include "../../common/heartbeat.hpp"

namespace sjsu::arm
{
    class RulesEngine
    {
    public:
        static constexpr int kMaxSpeed = 20;
        static constexpr int kMaxShoulderAngle = 90;

        mc_commands ValidateCommands(mc_commands commands)
        {
            // if(!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
            // {
            //     sjsu::LogInfo("Overriding joint speed");
            //     commands.speed = 0;
            //     return commands;
            // }

            if (!commands.is_operational)
            {
                // sjsu::LogWarning("Arm is not operational...");
                commands.speed = 0;
            }
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}