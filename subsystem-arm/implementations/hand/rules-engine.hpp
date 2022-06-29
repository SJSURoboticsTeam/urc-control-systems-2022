#pragma once
#include "../../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class RulesEngine
    {
        public:
        hand_arguments ValidateCommands(hand_arguments commands)
        {
            if(!heartbeat_.IsSyncedWithMissionControl(commands.hand_args.heartbeat_count))
            {
                commands.hand_args.speed = 0;
                sjsu::LogInfo("Overriding hand speed");
                return commands;
            }
            if(!commands.hand_args.is_operational)
            {
                commands.hand_args.speed = 0;
                sjsu::LogInfo("Hand is not operational... overriding speed");
            }
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        };

        private:
        sjsu::common::Heartbeat heartbeat_;
    };
}