#pragma once
#include "utility/math/units.hpp"
#include "sensor-dto.hpp"

namespace sjsu::arm
{
    struct joint_arguments
    {
        int speed = 0;
        int rotunda_angle = 0;
        int shoulder_angle = 0;
        int elbow_angle = 0;
        int wrist_pitch_angle = 0;
        int wrist_yaw_angle = 0;
        int is_operational = 0;
        int heartbeat_count = 0;
        char mode = 'A';

        void Print()
        {
            sjsu::LogInfo("ArmCommands\tMode\tRotunda\tShoulder\tElbow\tWrist\n");
            sjsu::LogInfo("\t%c\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", mode, rotunda_angle, shoulder_angle, elbow_angle, wrist_pitch_angle, wrist_yaw_angle);
            
        }
    };

    struct hand_arguments
    {
        int pinky_angle = 0;
        int ring_angle = 0;
        int middle_angle = 0;
        int index_angle = 0;
        int thumb_angle = 0;
        int is_operational = 0;
        int heartbeat_count = 0;
        char mode;

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
}