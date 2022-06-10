#pragma once
#include "../library/devices/actuators/servo/rmd_x.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::arm
{
    class ArmRouter
    {
    public:
        ArmRouter(sjsu::RmdX &rotunda, sjsu::RmdX &shoulder, sjsu::RmdX &elbow, sjsu::RmdX &left_wrist, sjsu::RmdX &right_wrist) : 
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
            rotunda_.SetAngle(units::angle::degree_t(arguments.rotunda_angle), units::angular_velocity::revolutions_per_minute_t(arguments.speed));
            shoulder_.SetAngle(units::angle::degree_t(arguments.shoulder_angle), units::angular_velocity::revolutions_per_minute_t(arguments.speed));
            elbow_.SetAngle(units::angle::degree_t(arguments.elbow_angle), units::angular_velocity::revolutions_per_minute_t(arguments.speed));
            left_wrist_.SetAngle(units::angle::degree_t(arguments.wrist_pitch_angle), units::angular_velocity::revolutions_per_minute_t(arguments.speed));
            right_wrist_.SetAngle(units::angle::degree_t(arguments.wrist_yaw_angle), units::angular_velocity::revolutions_per_minute_t(arguments.speed));
            return arguments;
        }

        void HomeArm(imu_accelerometers_feedback mpu_feedback, motors_feedback motors_feedback)
        {
            
        }

    private:
        sjsu::arm::arm_arguments arguments_;
        sjsu::RmdX &rotunda_;
        sjsu::RmdX &shoulder_;
        sjsu::RmdX &elbow_;
        sjsu::RmdX &left_wrist_;
        sjsu::RmdX &right_wrist_;
    };
}
