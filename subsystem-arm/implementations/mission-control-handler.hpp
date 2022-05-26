#pragma once
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{

    const char response_body_format[] = "";

    class MissionControlHandler
    {
    public:
        arm_commands ParseMissionControlData(std::string &response)
        {
        }
        std::string CreateGETRequestParameterWithRoverStatus()
        {
        }

    private:
        arm_commands commands;
        char request_parameter[300];
    };
}