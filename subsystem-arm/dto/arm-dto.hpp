#pragma once

#include <cstdint>

#include "utility/math/units.hpp"

namespace sjsu::arm
{
    // joint_angles order [rotunda, shoulder, elbow, wrist_pitch, wrist_yaw]
    // hand_angles order [pinky, ring, middle, index, thumb]
    const char kResponseBodyFormat[] = "{\"heartbeat_count\":%d,\"is_operational\":%d,\"arm_speed\":%d,\"joint_mode\":\"%c\",\"joint_angles\":[%d,%d,%d,%d,%d],\"hand_mode\":\"%c\",\"hand_angles\":[%d,%d,%d,%d,%d]}\n";

    const char kGETRequestFormat[] = "arm?heartbeat_count=%d&is_operational=%d&arm_speed=%d&joint_mode=\"%c\"&rotunda_angle=%d&shoulder_angle=%d&elbow_angle=%d&wrist_pitch_angle=%d&wrist_yaw_angle=%d&hand_mode=\"%c\"&pinky_angle=%d&ring_angle=%d&middle_angle=%d&index_angle=%d&thumb_angle=%d";

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
    };

    struct hand_arguments
    {
        int pinky_angle = 0;
        int ring_angle = 0;
        int middle_angle = 0;
        int index_angle = 0;
        int thumb_angle = 0;
        int finger_angle = 0;
        char mode = 'A';
    };

    struct arm_arguments
    {
        joint_arguments joint_args;
        hand_arguments hand_args;

        void Print()
        {
            printf(kResponseBodyFormat, joint_args.heartbeat_count, joint_args.is_operational, joint_args.speed, joint_args.mode, joint_args.rotunda_angle, joint_args.shoulder_angle, joint_args.elbow_angle, joint_args.wrist_pitch_angle, joint_args.wrist_yaw_angle, hand_args.mode, hand_args.pinky_angle, hand_args.ring_angle, hand_args.middle_angle, hand_args.index_angle, hand_args.thumb_angle);
        }
    };
}