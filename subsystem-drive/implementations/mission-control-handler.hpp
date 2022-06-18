#pragma once
#include "../dto/drive-dto.hpp"
#include <string>
#include <array>

namespace sjsu::drive
{
    const char response_body_format[] =
        "\r\n\r\n{\n"
        "  \"heartbeat_count\": %d,\n"
        "  \"is_operational\": %d,\n"
        "  \"wheel_shift\": %d,\n"
        "  \"drive_mode\": \"%c\",\n"
        "  \"speed\": %d,\n"
        "  \"angle\": %d\n"
        "}";
    class MissionControlHandler
    {
    public:
        drive_commands ParseMissionControlData(std::string &response)
        {
            int actual_arguments = sscanf(
                response.c_str(), response_body_format,
                &commands.heartbeat_count, &commands.is_operational, &commands.wheel_orientation,
                &commands.mode,&commands.speed, &commands.angle);

            return commands;
        }
        std::string CreateGETRequestParameterWithRoverStatus()
        {
            snprintf(
                request_parameter, 300,
                "drive?drive_mode=%c&speed=%d&angle=%d&wheel_orientation=%d",
                commands.mode, commands.speed, commands.angle, commands.wheel_orientation);
            return request_parameter;
        }

    private:
        drive_commands commands;
        char request_parameter[300];
    };

}