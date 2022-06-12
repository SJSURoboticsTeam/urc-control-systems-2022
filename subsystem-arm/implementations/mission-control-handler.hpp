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
        std::string CreateGETRequestParameterWithRoverStatus( imu_accelerometers_feedback mpus , motors_feedback motors, hand_arguments hand, arm_commands arm_)
        {
            snprintf( 
                request_parameter, 504,
                "?heartbeat_count=0&is_operational=0&arm_mode=%c&hand_mode=%c&rotunda_speed=%d"
                "&shoulder_speed%d&elbow_speed%d&wrist_speed%d&battery=0&rotunda_angle=%d&shoulder_angle=%d&elbow_angle=%d&wrist_"
                "roll=%d&wrist_pitch=%d&pinky_angle=%d&ring_angle=%d&middle_angle=%d&"
                "pointer_angle=%d&thumb_angle=%d"
                "&rountda_accel_x=%d&rountda_accel_y=%d&rountda_accel_z=%d"
                "&shoulder_accel_x=%d&shoulder_accel_y=%d&shoulder_accel_z=%d"
                "&elbow_accel_x=%d&elbow_accel_y=%d&elbow_accel_z=%d"
                "&wrist_accel_x=%d&wrist_accel_y=%d&wrist_accel_z=%d",
                arm_.mode,hand.mode,
                motors.rotunda_speed,motors.shoulder_speed,motors.elbow_speed,motors.wrist_speed,
                arm_.rotunda_angle,arm_.shoulder_angle,arm_.elbow_angle,arm_.wrist_yaw_angle,arm_.wrist_pitch_angle,
                hand.pinky_angle,hand.ring_angle,hand.middle_angle,hand.index_angle,hand.thumb_angle,
                mpus.rotunda.x, mpus.rotunda.y, mpus.rotunda.z, 
                mpus.shoulder.x, mpus.shoulder.y, mpus.shoulder.z, 
                mpus.elbow.x, mpus.elbow.y, mpus.elbow.z, 
                mpus.wrist.x, mpus.wrist.y, mpus.wrist.z
                );
            return request_parameter;
        }

    private:
        arm_commands commands;
        char request_parameter[504];
    };
}