#pragma once
#include "../dto/arm-dto.hpp"
#include "../dto/feedback-dto.hpp"

namespace sjsu::arm
{
    class MissionControlHandler
    {
    public:
        std::string CreateGETRequestParameterWithRoverStatus(arm_arguments arm)
        {
            char request_parameter[350];
            snprintf(
                request_parameter, 350, kGETRequestFormat,
                arm.joint_args.heartbeat_count, arm.joint_args.is_operational,
                arm.joint_args.mode, arm.joint_args.rotunda_angle, arm.joint_args.shoulder_angle,
                arm.joint_args.elbow_angle, arm.joint_args.wrist_pitch_angle, arm.joint_args.wrist_yaw_angle,
                arm.hand_args.mode, arm.hand_args.pinky_angle, arm.hand_args.ring_angle,
                arm.hand_args.middle_angle, arm.hand_args.index_angle, arm.hand_args.thumb_angle);
            return request_parameter;
        }

        arm_arguments ParseMissionControlData(std::string &response)
        {
            response = response.substr(response.find('{'));
            int actual_arguments = sscanf(response.c_str(), kResponseBodyFormat,
                                          &arguments_.joint_args.heartbeat_count, &arguments_.joint_args.is_operational, &arguments_.joint_args.mode,
                                          &arguments_.joint_args.rotunda_angle, &arguments_.joint_args.shoulder_angle, &arguments_.joint_args.elbow_angle,
                                          &arguments_.joint_args.wrist_pitch_angle, &arguments_.joint_args.wrist_yaw_angle);
            if (actual_arguments != kExpectedNumberOfArguments)
            {
                sjsu::LogError("Received %d expected %d arguments", actual_arguments, kExpectedNumberOfArguments);
            }
            return arguments_;
        }

    private:
        arm_arguments arguments_;
        const int kExpectedNumberOfArguments = 8;
    };
}