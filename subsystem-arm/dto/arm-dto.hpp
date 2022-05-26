#pragma once
#include "utility/math/units.hpp"

namespace sjsu::arm{
    struct arm_commands
    {
        int rotunda_angle = 0;
        int shoulder_angle = 0;
        int elbow_angle = 0;
        int wrist_pitch_angle = 0;
        int wrist_yaw_angle = 0;
        int finger_angle = 0;
        char mode = 'A';

        void Print()
        {}
    };

    struct arm_arguments
    {
        int rotunda_angle = 0;
        int shoulder_angle = 0;
        int elbow_angle = 0;
        int wrist_pitch_angle = 0;
        int wrist_yaw_angle = 0;

        void Print()
        {}
    };

    struct accelerometer_feedback
    {
        int x = 0;
        int y = 0;
        int z = 0;
    };

    struct imu_accelerometers_feedback
    {
        accelerometer_feedback rotunda{};
        accelerometer_feedback shoulder{};
        accelerometer_feedback elbow{};
        accelerometer_feedback wrist{};

        void Print()
        {}
    };

    struct motors_feedback
    {
        units::angular_velocity::revolutions_per_minute_t rotunda_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t shoulder_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t elbow_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t wrist_speed = 0_rpm;
        units::angle::degree_t  rotunda_angle = 0_deg;
        units::angle::degree_t  shoulder_angle = 0_deg;
        units::angle::degree_t  elbow_angle = 0_deg;
        units::angle::degree_t  wrist_angle = 0_deg;
        
        void Print()
        {}
    };
}