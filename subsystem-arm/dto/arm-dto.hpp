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
        char mode = 'A';

        void Print()
        {
            sjsu::LogInfo("ArmCommands\tMode\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%c\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", mode, rotunda_angle, shoulder_angle, elbow_angle, wrist_pitch_angle, wrist_yaw_angle);
            
        }
    };

    struct arm_arguments
    {
        int rotunda_angle = 0;
        int shoulder_angle = 0;
        int elbow_angle = 0;
        int wrist_pitch_angle = 0;
        int wrist_yaw_angle = 0;

        void Print()
        {
            sjsu::LogInfo("ArmArguments\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", rotunda_angle, shoulder_angle, elbow_angle, wrist_pitch_angle, wrist_yaw_angle);
        }
    };

    struct hand_arguments
    {
        int pinky_angle = 0;
        int ring_angle = 0;
        int middle_angle = 0;
        int index_angle = 0;
        int thumb_angle = 0;
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
        {
            sjsu::LogInfo("AccelerometerFeedbackX\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", rotunda.x, shoulder.x, elbow.x, wrist.x);
            sjsu::LogInfo("AccelerometerFeedbackY\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", rotunda.y, shoulder.y, elbow.y, wrist.y);
            sjsu::LogInfo("AccelerometerFeedbackZ\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", rotunda.z, shoulder.z, elbow.z, wrist.z);

        }
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
        {
            sjsu::LogInfo("MotorsFeedback\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", (rotunda_speed), (shoulder_speed), (elbow_speed), (wrist_speed));
            sjsu::LogInfo("MotorsFeedbackAngle\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", (rotunda_angle), (shoulder_angle), (elbow_angle), (wrist_angle));
        }
    };
}