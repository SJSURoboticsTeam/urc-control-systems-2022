#pragma once
#include "utility/log.hpp"
#include "../dto/arm-dto.hpp"
#include "../common/heartbeat.hpp"

namespace sjsu::arm
{

    class JointsRulesEngine
    {
    public:
        static constexpr int kMaxShoulderAngle = 90;
        static constexpr int kMaxSpeed = 20;

        arm_arguments ValidateCommands(arm_arguments commands)
        {
            // if(!heartbeat_.IsSyncedWithMissionControl(commands.joint_args.heartbeat_count))
            // {
            //     sjsu::LogInfo("Overriding joint speed");
            //     commands.joint_args.speed = 0;
            //     return commands;
            // }

            if (!commands.joint_args.is_operational)
            {
                sjsu::LogInfo("Joint is not operational... overriding speed");
                commands.joint_args.speed = 0;
            }

            if (commands.joint_args.speed > kMaxSpeed || commands.joint_args.speed < -kMaxSpeed)
            {
                sjsu::LogInfo("Specified joint speed is too fast... clamping speed");
                commands.joint_args.speed = std::clamp(commands.joint_args.speed, -kMaxSpeed, kMaxSpeed);
            }

            // if (commands.joint_args.shoulder_angle > kMaxShoulderAngle || commands.joint_args.shoulder_angle < -kMaxShoulderAngle)
            // {
            //     std::clamp(commands.joint_args.shoulder_angle, -kMaxShoulderAngle, kMaxShoulderAngle);
            // }
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}