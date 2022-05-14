#pragma once
#include "../dto/drive-dto.hpp"
#include "../utility/log.hpp"

namespace sjsu::drive
{
    class MissionControlHandler
    {
    public:
        static drive_commands ParseMissionControlData(std::string &response)
        {
            int actual_arguments = sscanf(
                response.c_str(), response_body_format,
                &commands.mode, &commands.speed, &commands.angle,
                &commands.wheel_orientation);

            return commands;
        }

        static std::string CreateGETRequestParameterWithRoverStatus()
        {
            snprintf(
                request_parameter, 300,
                "?drive_mode=%c&speed=%d&angle=%d&wheel_orientation=%d",
                commands.mode, commands.speed, commands.angle, commands.wheel_orientation);
            return request_parameter;
        }

    private:
        drive_commands commands;
        char request_parameter[300];
        const char response_body_format[] =
            "\r\n\r\n{\n"
            "  \"drive_mode\": \"%c\",\n"
            "  \"speed\": %d,\n"
            "  \"angle\": %d\n"
            "  \"wheel_orientation\": %d,\n"
            "}";
    };

}