#pragma once

#include <cstdint>

#include "utility/math/units.hpp"

namespace sjsu::arm
{
    // joint_angles order [rotunda, shoulder, elbow, wrist_pitch, wrist_yaw]
    // hand_angles order [pinky, ring, middle, index, thumb]
    const char kResponseBodyFormat[] = "{\"heartbeat_count\":%d,\"is_operational\":%d,\"speed\":%d,\"angles\":[%d,%d,%d,%d,%d,%d]}\n";
    const char kGETRequestFormat[] = "arm?heartbeat_count=%d&is_operational=%d&speed=%d&joint_mode=%c&rotunda_angle=%d&shoulder_angle=%d&elbow_angle=%d&wrist_pitch_angle=%d&wrist_yaw_angle=%d&hand_mode=%c&pinky_angle=%d&ring_angle=%d&middle_angle=%d&index_angle=%d&thumb_angle=%d";

    struct joint_arguments
    {
        int speed = 2;
        int rotunda_angle = 0;
        int shoulder_angle = 0;
        int elbow_angle = 0;
        int wrist_pitch_angle = 0;
        int wrist_roll_angle = 0;
    };

    struct hand_arguments
    {
        int speed = 2;
        int pinky_angle = 0;
        int ring_angle = 0;
        int middle_angle = 0;
        int index_angle = 0;
        int thumb_angle = 0;
    };

    struct rr9_arguments
    {
        int angle = 0;
    };

    struct mc_commands
    {
        int heartbeat_count = 0;
        int is_operational = 0;
        int speed = 2;
        char mode = 'J';
        int first_angle = 0;
        int second_angle = 0;
        int third_angle = 0;
        int fourth_angle = 0;
        int fifth_angle = 0;
        int sixth_angle = 0;
        void Print()
        {
            printf(kResponseBodyFormat, heartbeat_count, is_operational, speed, first_angle, second_angle, third_angle, fourth_angle, fifth_angle, sixth_angle);
        }
    };

    struct arm_arguments
    {
        int speed = 0;
        int rotunda_angle = 0;
        int shoulder_angle = 0;
        int elbow_angle = 0;
        int wrist_pitch_angle = 0;
        int wrist_roll_angle = 0;
        int end_effector_angle = 0;
    };
}