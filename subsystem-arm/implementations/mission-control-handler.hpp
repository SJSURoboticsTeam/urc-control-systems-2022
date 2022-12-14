#pragma once
#include "../dto/arm-dto.hpp"
#include "../dto/feedback-dto.hpp"

namespace sjsu::arm
{
    class MissionControlHandler
    {
    public:
        std::string CreateGETRequestParameterWithRoverStatus(mc_commands commands)
        {
            char request_parameter[350];
            snprintf(
                request_parameter, 350, kGETRequestFormat,
                commands.heartbeat_count, commands.is_operational, commands.speed,
                commands.rotunda_angle, commands.shoulder_angle,
                commands.elbow_angle, commands.wrist_pitch_angle, commands.wrist_roll_angle, commands.rr9_angle);
            return request_parameter;
        }

        mc_commands ParseMissionControlData(std::string &response)
        {
            response = response.substr(response.find('{'));
            int actual_arguments = sscanf(response.c_str(), kResponseBodyFormat,
                                          &commands_.heartbeat_count, &commands_.is_operational, &commands_.speed, &commands_.rotunda_angle, &commands_.shoulder_angle, &commands_.elbow_angle, &commands_.wrist_pitch_angle, &commands_.wrist_roll_angle, &commands_.rr9_angle);
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