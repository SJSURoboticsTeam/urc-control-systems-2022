#pragma once
#include "../dto/drive-dto.hpp"
#include <string>
#include <array>

namespace sjsu::drive
{
    class MissionControlHandler
    {
    public:
        std::string CreateGETRequestParameterWithRoverStatus()
        {
            drive_commands commands;
            char request_parameter[300];
            snprintf(
                request_parameter, 300, kGETRequestFormat,
                commands.mode, commands.speed, commands.angle, commands.wheel_orientation);
            return request_parameter;
        }

        drive_commands ParseMissionControlData(std::string &response)
        {
            drive_commands commands;
            int actual_arguments = sscanf(
                response.c_str(), kResponseBodyFormat,
                &commands.heartbeat_count, &commands.is_operational, &commands.wheel_orientation,
                &commands.mode, &commands.speed, &commands.angle);
            return commands;
        }
    };

}