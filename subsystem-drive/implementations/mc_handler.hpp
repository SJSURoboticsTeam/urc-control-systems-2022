#pragma once
#include "../dto/drive-dto.hpp"
#include "../utility/log.hpp"

namespace sjsu::drive
{
    class MCHandler
    {
    public:
        static drive_commands ParseData(std::string &response)
        {
            drive_commands commands;
            int actual_arguments = sscanf(
                response.c_str(), response_body_format,
                &commands.mode, &commands.speed, &commands.angle,
                &commands.wheel_orientation);

            return commands;
        }

    private:
        const char response_body_format[] =
            "\r\n\r\n{\n"
            "  \"drive_mode\": \"%c\",\n"
            "  \"speed\": %d,\n"
            "  \"angle\": %d\n"
            "  \"wheel_orientation\": %d,\n"
            "}";
    };

}