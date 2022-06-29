#pragma once
#include "utility/log.hpp"
#include "../../dto/arm-dto.hpp"
#include "../../common/heartbeat.hpp"

namespace sjsu::arm
{
    class RulesEngine
    {
    public:
        static constexpr int kMaxFingerAngle = 180;

        hand_arguments ValidateCommands(hand_arguments commands)
        {
            if (!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
            {
                sjsu::LogInfo("Hand was unsynced, holding previous state!");
                return previous_commands;
            }
            if (!commands.is_operational)
            {
                sjsu::LogInfo("Hand is not operational... holding previous state!");
                return previous_commands;
            }
            if (commands.index_angle > 180) // WIP: Potential issue with desyncing and previous commands not being clamped
            {
                commands.index_angle = 180;
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