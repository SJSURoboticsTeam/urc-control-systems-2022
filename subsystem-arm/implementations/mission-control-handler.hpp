#pragma once
#include "../dto/arm-dto.hpp"
#include "../dto/feedback-dto.hpp"

namespace sjsu::arm
{

    const char response_body_format[] = "";
    //this parses both hand and joints data
    class MissionControlHandler
    {
    public:
        // TODO
        arm_arguments ParseMissionControlData(std::string &response)
        {
            int actual_arguments = sscanf(
                response.c_str(), response_body_format,
                &arguments.joint_args.rotunda_angle, &arguments.joint_args.shoulder_angle, &arguments.joint_args.elbow_angle,
                &arguments.joint_args.wrist_pitch_angle, &arguments.joint_args.wrist_yaw_angle, &arguments.joint_args.mode);
                return arguments;
        }
        std::string CreateGETRequestParameterWithRoverStatus(arm_accelerometer_feedback mpus, motors_feedback motors, hand_arguments hand, arm_arguments arm)
        {
            snprintf(
                request_parameter, 600,
                "?heartbeat_count=%d&is_operational=%d&arm_mode=%c&hand_mode=%c&rotunda_speed=%d"
                "&shoulder_speed=%d&elbow_speed=%d&wrist_speed=%d&battery=0&rotunda_angle=%d&shoulder_angle=%d&elbow_angle=%d&wrist_"
                "roll=%d&wrist_pitch=%d&pinky_angle=%d&ring_angle=%d&middle_angle=%d&pointer_angle=%d&thumb_angle=%d&finger_angle=%d"
                "&rountda_accel_x=%d&rountda_accel_y=%d&rountda_accel_z=%d&shoulder_accel_x=%d&shoulder_accel_y=%d&shoulder_accel_z=%d"
                "&elbow_accel_x=%d&elbow_accel_y=%d&elbow_accel_z=%d&wrist_accel_x=%d&wrist_accel_y=%d&wrist_accel_z=%d",
                arm.joint_args.heartbeat_count, arm.joint_args.is_operational, arm.hand_args.mode, hand.mode,
                static_cast<int>(motors.rotunda_speed), static_cast<int>(motors.shoulder_speed), static_cast<int>(motors.elbow_speed), static_cast<int>(motors.wrist_speed),
                arm.joint_args.rotunda_angle, arm.joint_args.shoulder_angle, arm.joint_args.elbow_angle, arm.joint_args.wrist_yaw_angle, arm.joint_args.wrist_pitch_angle,
                hand.pinky_angle, hand.ring_angle, hand.middle_angle, hand.index_angle, hand.thumb_angle, hand.finger_angle,
                mpus.rotunda.x, mpus.rotunda.y, mpus.rotunda.z,
                mpus.shoulder.x, mpus.shoulder.y, mpus.shoulder.z,
                mpus.elbow.x, mpus.elbow.y, mpus.elbow.z,
                mpus.wrist.x, mpus.wrist.y, mpus.wrist.z);
            return request_parameter;
        }

    private:
        arm_arguments arguments;
        char request_parameter[504];
    };
}