#pragma once
#include <string>
#include <array>

#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class MissionControlHandler
    {
    public:
        std::string CreateGETRequestParameterWithRoverStatus(drive_commands commands)
        {
            char request_parameter[200];
            snprintf(
                request_parameter, 200, kGETRequestFormat,
                commands.heartbeat_count, commands.is_operational, commands.wheel_orientation, commands.mode, commands.speed, commands.angle);
            return request_parameter;
        }

        drive_commands ParseMissionControlData(std::string &response)
        {
            response = response.substr(response.find('{'));
            int actual_arguments = sscanf(
                response.c_str(), kResponseBodyFormat,
                &commands_.heartbeat_count, &commands_.is_operational, &commands_.wheel_orientation,
                &commands_.mode, &commands_.speed, &commands_.angle);
            if (actual_arguments != kExpectedNumberOfArguments)
            {
                sjsu::LogError("Received %d arguments, expected %d", actual_arguments, kExpectedNumberOfArguments);
            }
            return commands_;
        }

    private:
        drive_commands commands_;
        const int kExpectedNumberOfArguments = 6;
    };

}