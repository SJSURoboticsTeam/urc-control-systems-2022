#pragma once

#include <cstdint>

#include "utility/math/units.hpp"

namespace sjsu::arm
{
    // joint_angles order [rotunda, shoulder, elbow, wrist_pitch, wrist_yaw]
    // hand_angles order [pinky, ring, middle, index, thumb]
    const char kResponseBodyFormat[] = "{\"heartbeat_count\":%d,\"is_operational\":%d,\"mode\":\"%c\",\"angles\":[%d,%d,%d,%d,%d]}\n";
    const char kGETRequestFormat[] = "arm?heartbeat_count=%d&is_operational=%d&speed=%d&joint_mode=%c&rotunda_angle=%d&shoulder_angle=%d&elbow_angle=%d&wrist_pitch_angle=%d&wrist_yaw_angle=%d&hand_mode=%c&pinky_angle=%d&ring_angle=%d&middle_angle=%d&index_angle=%d&thumb_angle=%d";

    struct joint_arguments
    {
        int heartbeat_count = 0;
        int is_operational = 0;
        int speed = 5;
        char mode = 'S';
        int rotunda_angle = 0;
        int shoulder_angle = 0;
        int elbow_angle = 0;
        int wrist_pitch_angle = 0;
        int wrist_roll_angle = 0;
    };

    struct hand_arguments
    {
        char mode = 'I';
        int pinky_angle = 88;
        int ring_angle = 88;
        int middle_angle = 88;
        int index_angle = 88;
        int thumb_angle = 88;
    };
    struct arm_arguments
    {
        joint_arguments joint_args;
        hand_arguments hand_args;

        void Print()
        {
            printf(kResponseBodyFormat, joint_args.heartbeat_count, joint_args.is_operational, joint_args.mode, joint_args.rotunda_angle, joint_args.shoulder_angle, joint_args.elbow_angle, joint_args.wrist_pitch_angle, joint_args.wrist_roll_angle);
        }
    };
}