#pragma once
#include "utility/log.hpp"
#include "../../dto/arm-dto.hpp"
#include "../../common/heartbeat.hpp"

namespace sjsu::arm
{
    class HandRulesEngine
    {
    public:
        static constexpr int kMaxFingerAngle = 180;
        static constexpr int kMinFingerAngle = 0;

        hand_arguments ValidateCommands(hand_arguments commands)
        {
            if (commands.thumb_angle > kMaxFingerAngle || commands.thumb_angle < kMinFingerAngle)
            {
                sjsu::LogWarning("Thumb angle is out of bounds... clamping to limit");
                commands.thumb_angle = std::clamp(commands.thumb_angle, kMinFingerAngle, kMaxFingerAngle);
            }
            if (commands.index_angle > kMaxFingerAngle || commands.index_angle < kMinFingerAngle)
            {
                sjsu::LogWarning("Index finger angle is out of bounds... clamping to limit");
                commands.index_angle = std::clamp(commands.index_angle, kMinFingerAngle, kMaxFingerAngle);
            }
            if (commands.middle_angle > kMaxFingerAngle || commands.middle_angle < kMinFingerAngle)
            {
                sjsu::LogWarning("Middle finger angle is out of bounds... clamping to limit");
                commands.middle_angle = std::clamp(commands.middle_angle, kMinFingerAngle, kMaxFingerAngle);
            }
            if (commands.ring_angle > kMaxFingerAngle || commands.ring_angle < kMinFingerAngle)
            {
                sjsu::LogWarning("Ring finger angle is out of bounds... clamping to limit");
                commands.ring_angle = std::clamp(commands.ring_angle, kMinFingerAngle, kMaxFingerAngle);
            }
            if (commands.pinky_angle > kMaxFingerAngle || commands.pinky_angle < kMinFingerAngle)
            {
                sjsu::LogWarning("Pinky finger angle is out of bounds... clamping to limit");
                commands.pinky_angle = std::clamp(commands.pinky_angle, kMinFingerAngle, kMaxFingerAngle);
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