#pragma once
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{

    const char response_body_format[] = "";
    //this parses both hand and joints data
    class MissionControlHandler
    {
    public:
        void ParseMissionControlData(std::string &response, joint_arguments &joint_argument, hand_arguments &hand_argument)
        {
              int actual_arguments = sscanf(
                response.c_str(), response_body_format,
                &joint_argument.rotunda_angle, &joint_argument.shoulder_angle, &joint_argument.elbow_angle,
                &joint_argument.wrist_pitch_angle, &joint_argument.wrist_yaw_angle, &joint_argument.mode);
        }
        
        std::string CreateGETRequestParameterWithRoverStatus(arm_accelerometer_feedback mpus , motors_feedback motors)
        {
            // snprintf(
            //     request_parameter, 300,
            //     "arm?arm_mode=%crotunda_x=%d&rotunda_y=%d&rotunda_z=%d",
            //     joint_argument.mode,
            //     mpus.rotunda.x, mpus.rotunda.y, mpus.rotunda.z, 
            //     commands.wrist_yaw_angle);
            // return request_parameter;
        }

    private:
        char request_parameter[300];
    };
}