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
        }
    };
}