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
        // placeholder values below
        static constexpr int kMinShoulderAngle = 0;
        static constexpr int kMaxShoulderAngle = 90;
        static constexpr int kMinElbowAngle = -150;
        static constexpr int kMaxElbowAngle = 150;
        static constexpr int kMinWristPitchAngle = -90;
        static constexpr int kMaxWristPitchAngle = 90;

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


            if(commands.mode == 'H'){
                commands.first_angle = std::clamp(commands.first_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.second_angle = std::clamp(commands.second_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.third_angle = std::clamp(commands.third_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.fourth_angle = std::clamp(commands.fourth_angle, kMinFingerAngle, kMaxFingerAngle);
                commands.fifth_angle = std::clamp(commands.fifth_angle, kMinFingerAngle, kMaxFingerAngle);
            }
            else if (commands.mode == 'J'){
                commands.second_angle = std::clamp(commands.second_angle, kMinShoulderAngle, kMaxShoulderAngle);
                commands.third_angle = std::clamp(commands.third_angle, kMinElbowAngle, kMaxElbowAngle);
                commands.fourth_angle = std::clamp(commands.fourth_angle, kMinWristPitchAngle, kMaxWristPitchAngle);
            }
            else{ // Going to be RRNineMode

            }

            if(commands.mode)
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}