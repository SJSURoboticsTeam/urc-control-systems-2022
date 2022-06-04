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
              int actual_arguments = sscanf(
                response.c_str(), response_body_format,
                &commands.rotunda_angle, &commands.shoulder_angle, &commands.elbow_angle,
                &commands.wrist_pitch_angle, &commands.wrist_yaw_angle, &commands.mode);

            return commands;
        }
        std::string CreateGETRequestParameterWithRoverStatus( imu_accelerometers_feedback mpus , motors_feedback motors)
        {
            snprintf(
                request_parameter, 300,
                "arm?arm_mode=%crotunda_x=%d&rotunda_y=%d&rotunda_z=%d",
                commands.mode,
                mpus.rotunda.x, mpus.rotunda.y, mpus.rotunda.z, 
                commands.wrist_yaw_angle);
            return request_parameter
        }

    private:
        arm_commands commands;
        char request_parameter[300];
    };
}