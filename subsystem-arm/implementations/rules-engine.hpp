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
                // sjsu::LogWarning("Arm is not operational...");
                commands.joint_args.speed = 0;
            }

            commands.hand_args.pinky_angle = std::clamp(commands.hand_args.pinky_angle, kMinFingerAngle, kMaxFingerAngle);
            commands.hand_args.ring_angle = std::clamp(commands.hand_args.ring_angle, kMinFingerAngle, kMaxFingerAngle);
            commands.hand_args.middle_angle = std::clamp(commands.hand_args.middle_angle, kMinFingerAngle, kMaxFingerAngle);
            commands.hand_args.index_angle = std::clamp(commands.hand_args.index_angle, kMinFingerAngle, kMaxFingerAngle);
            commands.hand_args.thumb_angle = std::clamp(commands.hand_args.thumb_angle, kMinFingerAngle, kMaxFingerAngle);

            commands.joint_args.speed = std::clamp(commands.joint_args.speed, -kMaxSpeed, kMaxSpeed);

            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}