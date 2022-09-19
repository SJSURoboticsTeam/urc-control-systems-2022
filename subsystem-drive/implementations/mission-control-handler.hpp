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
                commands.mode, commands.speed, commands.angle, commands.wheel_orientation);
            return request_parameter;
        }

        drive_commands ParseMissionControlData(std::string &response)
        {
            int actual_arguments = sscanf(
                response.c_str(), kResponseBodyFormat,
                &commands_.heartbeat_count, &commands_.is_operational, &commands_.wheel_orientation,
                &commands_.mode, &commands_.speed, &commands_.angle);
            return commands_;
        }

    private:
        drive_commands commands_;
    };

}