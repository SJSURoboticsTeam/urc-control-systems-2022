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
            if(!heartbeat_.IsSyncedWithMissionControl(commands.joint_args.heartbeat_count))
            {
                commands.joint_args.speed = 0;
                sjsu::LogInfo("Overriding joint speed");
                return commands;
            }
            if(!commands.joint_args.is_operational)
            {
                commands.joint_args.speed = 0;
                sjsu::LogInfo("Joint is not operational... overriding speed");
            }
            if(commands.joint_args.speed > kMaxSpeed || commands.joint_args.speed < -kMaxSpeed)
            {
                commands.joint_args.speed = std::clamp(commands.joint_args.speed, -kMaxSpeed, kMaxSpeed);
                sjsu::LogInfo("Specified joint speed is too fast... clamping speed");
            }
            if(commands.joint_args.shoulder_angle > kMaxShoulderAngle || commands.joint_args.shoulder_angle < -kMaxShoulderAngle)
            {
                std::clamp(commands.joint_args.shoulder_angle, -kMaxShoulderAngle, kMaxShoulderAngle);
            }
            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }
        private:
        sjsu::common::Heartbeat heartbeat_;
    };
}