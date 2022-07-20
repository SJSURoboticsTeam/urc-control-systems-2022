#pragma once
#include "../library/devices/actuators/servo/rmd_x.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::arm
{
    class JointRouter
    {
    public:
        JointRouter(sjsu::RmdX &rotunda, sjsu::RmdX &shoulder, sjsu::RmdX &elbow, sjsu::RmdX &left_wrist, sjsu::RmdX &right_wrist) : 
        rotunda_(rotunda), shoulder_(shoulder), elbow_(elbow), left_wrist_(left_wrist), right_wrist_(right_wrist) {}

        void Initialize()
        {
            rotunda_.Initialize();
            shoulder_.Initialize();
            elbow_.Initialize();
            left_wrist_.Initialize();
            right_wrist_.Initialize();
        };

        arm_arguments SetArmArguments(arm_arguments arguments)
        {
            rotunda_.SetAngle(units::angle::degree_t(arguments.joint_args.rotunda_angle), units::angular_velocity::revolutions_per_minute_t(arguments.joint_args.speed));
            shoulder_.SetAngle(units::angle::degree_t(arguments.joint_args.shoulder_angle), units::angular_velocity::revolutions_per_minute_t(arguments.joint_args.speed));
            elbow_.SetAngle(units::angle::degree_t(arguments.joint_args.elbow_angle), units::angular_velocity::revolutions_per_minute_t(arguments.joint_args.speed));
            left_wrist_.SetAngle(units::angle::degree_t(arguments.joint_args.wrist_pitch_angle), units::angular_velocity::revolutions_per_minute_t(arguments.joint_args.speed));
            right_wrist_.SetAngle(units::angle::degree_t(arguments.joint_args.wrist_yaw_angle), units::angular_velocity::revolutions_per_minute_t(arguments.joint_args.speed));
            return arguments;
        }

       // void HomeArm(arm_accelerometer_feedback mpu_feedback, motors_feedback motors_feedback)
          void HomeArm() 
        {
            initial_rotunda_position_  = MapEncoderDataToDegrees(rotunda_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_shoulder_position_  = MapEncoderDataToDegrees(shoulder_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_elbow_position_  = MapEncoderDataToDegrees(elbow_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_left_wrist_position_  = MapEncoderDataToDegrees(left_wrist_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_right_wrist_position_  = MapEncoderDataToDegrees(right_wrist_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
        }

    private:


        float initial_rotunda_position_ = 0;
        float initial_shoulder_position_ = 0;
        float initial_elbow_position_ = 0;
        float initial_left_wrist_position_ = 0;
        float initial_right_wrist_position_ = 0;

        /// takes data from encoder and maps it to degrees
        float MapEncoderDataToDegrees(float encoder_data)
        {
            return (60.0 * encoder_data / 256.0);
        }
        sjsu::arm::arm_arguments arguments_;
        sjsu::RmdX &rotunda_;
        sjsu::RmdX &shoulder_;
        sjsu::RmdX &elbow_;
        sjsu::RmdX &left_wrist_;
        sjsu::RmdX &right_wrist_;
    };
}
