#pragma once
#include "utility/log.hpp"
#include "utility/math/units.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

#include "../../dto/arm-dto.hpp"
#include "../../../common/rmd-encoder.hpp"

namespace sjsu::arm
{
    class JointRouter
    {
    public:
        JointRouter(sjsu::RmdX &rotunda, sjsu::RmdX &shoulder, sjsu::RmdX &elbow, sjsu::RmdX &left_wrist, sjsu::RmdX &right_wrist) : rotunda_(rotunda), shoulder_(shoulder), elbow_(elbow), left_wrist_(left_wrist), right_wrist_(right_wrist) {}

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
            left_wrist_.SetAngle(units::angle::degree_t(arguments.joint_args.wrist_pitch_angle + arguments.joint_args.wrist_roll_angle), units::angular_velocity::revolutions_per_minute_t(arguments.joint_args.speed));
            right_wrist_.SetAngle(units::angle::degree_t(-arguments.joint_args.wrist_pitch_angle + arguments.joint_args.wrist_roll_angle), units::angular_velocity::revolutions_per_minute_t(arguments.joint_args.speed));
            return arguments;
        }

        void HomeArm()
        {
            sjsu::LogInfo("Homing arm...");
            initial_rotunda_position_ = common::RmdEncoder::CalcEncoderPositions(rotunda_);
            initial_shoulder_position_ = common::RmdEncoder::CalcEncoderPositions(shoulder_);
            initial_elbow_position_ = common::RmdEncoder::CalcEncoderPositions(elbow_);
            initial_left_wrist_position_ = common::RmdEncoder::CalcEncoderPositions(left_wrist_);
            initial_right_wrist_position_ = common::RmdEncoder::CalcEncoderPositions(right_wrist_);
        }

    private:
        float initial_rotunda_position_ = 0;
        float initial_shoulder_position_ = 0;
        float initial_elbow_position_ = 0;
        float initial_left_wrist_position_ = 0;
        float initial_right_wrist_position_ = 0;

        sjsu::arm::arm_arguments arguments_;
        sjsu::RmdX &rotunda_;
        sjsu::RmdX &shoulder_;
        sjsu::RmdX &elbow_;
        sjsu::RmdX &left_wrist_;
        sjsu::RmdX &right_wrist_;
    };
}
