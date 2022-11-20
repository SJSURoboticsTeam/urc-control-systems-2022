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
        static constexpr int kMinFingerAngle = 88;
        static constexpr int kMaxFingerAngle = 175;
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
            else {
                commands.speed = 5;
            }
            if(commands.mode != 'J'){
                commands.first_angle = std::clamp(commands.first_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.second_angle = std::clamp(commands.second_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.third_angle = std::clamp(commands.third_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.fourth_angle = std::clamp(commands.fourth_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.fifth_angle = std::clamp(commands.fifth_angle, kMinFingerAngle, kMaxFingerAngle);
            }
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}