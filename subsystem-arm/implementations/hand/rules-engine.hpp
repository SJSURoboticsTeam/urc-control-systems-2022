#pragma once
#include "utility/log.hpp"
#include "../../dto/arm-dto.hpp"
#include "../../common/heartbeat.hpp"

namespace sjsu::arm
{
    class RulesEngine
    {
    public:
        hand_arguments ValidateCommands(hand_arguments commands)
        {
            if (!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
            {
                sjsu::LogInfo("Hand was unsynced, holding previous state!");
                return previous_commands;
            }
            if (!commands.is_operational)
            {
                sjsu::LogInfo("Hand is not operational... overriding speed");
                return previous_commands;
            }
            heartbeat_.IncrementHeartbeatCount();
            previous_commands = commands;
            return commands;
        };

    private:
        sjsu::common::Heartbeat heartbeat_;
        hand_arguments previous_commands;
    };
}