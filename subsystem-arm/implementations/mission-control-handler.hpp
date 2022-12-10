#pragma once
#include "../dto/arm-dto.hpp"
#include "../dto/feedback-dto.hpp"

namespace sjsu::arm
{
    class MissionControlHandler
    {
    public:
        std::string CreateGETRequestParameterWithRoverStatus(arm_arguments arm, mc_commands commands)
        {
            char request_parameter[350];
            // TODO: Fix this for the new arm dto
            //  snprintf(
            //      request_parameter, 350, kGETRequestFormat,
            //      commands.heartbeat_count, commands.is_operational, arm.speed,
            //      commands.mode, arm.rotunda_angle, arm.shoulder_angle,
            //      arm.elbow_angle, arm.wrist_pitch_angle, arm.wrist_roll_angle,
            //      commands.mode, arm.hand_args.pinky_angle, arm.hand_args.ring_angle,
            //      arm.hand_args.middle_angle, arm.hand_args.index_angle, arm.hand_args.thumb_angle);
            return request_parameter;
        }

        mc_commands ParseMissionControlData(std::string &response)
        {
            response = response.substr(response.find('{'));
            int actual_arguments = sscanf(
                response.c_str(), kResponseBodyFormat,
                &commands_.heartbeat_count, &commands_.is_operational, &commands_.speed, &commands_.first_angle, &commands_.second_angle, &commands_.third_angle, &commands_.fourth_angle, &commands_.fifth_angle, &commands_.sixth_angle);
            if (actual_arguments != kExpectedNumberOfArguments)
            {
                sjsu::LogError("Received %d expected %d arguments", actual_arguments, kExpectedNumberOfArguments);
            }
            return commands_;
        }

    private:
        mc_commands commands_;
        const int kExpectedNumberOfArguments = 9;
    };
}