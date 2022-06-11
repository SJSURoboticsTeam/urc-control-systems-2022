#pragma once

#include "../dto/arm-dto.hpp"
#include "../common/heartbeat.hpp"

namespace sjsu::arm
{

    class RulesEngine
    {
        public:
        static constexpr int kMaxShoulderAngle = 90;
        static constexpr int kMaxSpeed = 20;
        arm_commands ValidateCommands(arm_commands commands)
        {
            if(!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
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
            if(commands.speed > kMaxSpeed || commands.speed < -kMaxSpeed)
            {
                commands.speed = std::clamp(commands.speed, -kMaxSpeed, kMaxSpeed);
                sjsu::LogInfo("Specified speed is too fast... clamping speed");
            }
            if(commands.shoulder_angle > kMaxShoulderAngle || commands.shoulder_angle < -kMaxShoulderAngle)
            {
                std::clamp(commands.shoulder_angle, -kMaxShoulderAngle, kMaxShoulderAngle);
            } 
            
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }
        private:
        sjsu::common::Heartbeat hearbeat_;
    };
}