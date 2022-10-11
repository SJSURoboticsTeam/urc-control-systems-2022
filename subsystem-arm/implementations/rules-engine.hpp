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
        
        static constexpr int kRotundaAngle = 480;
        int kMaxShoulderAngle = 90;
        int kMinShoulderAngle = 90;
        int kMaxElbowAngle = 90;
        int kMinElbowAngle = 90; 
        int kMaxWristPitchAngle = 20;
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
            
            //To prevent wire strangulation of via the rotunda
            commands.joint_args.rotunda_angle = std::clamp(commands.joint_args.rotunda_angle,-kRotundaAngle,kRotundaAngle;)

            // if elbow goes below the body
            if(commands.joint_args.shoulder_angle < 45)
                //block the elbow from going below a certain angle
                kMinElbowAngle = -45
            if(commands.joint_args.shoulder_angle < -45)
                kMaxElbowAngle = 45;



            commands.joint_args.wrist_pitch_angle

            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
    };
}