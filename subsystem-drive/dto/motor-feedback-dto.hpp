#pragma once
#include "utility/math/units.hpp"

namespace sjsu::drive{

    struct motor_feedback{
        units::angular_velocity::revolutions_per_minute_t left_steer_speed = 5_rpm;
        units::angular_velocity::revolutions_per_minute_t right_steer_speed = 5_rpm;
        units::angular_velocity::revolutions_per_minute_t back_steer_speed = 5_rpm;
    };

}