#pragma once
#include "utility/math/units.hpp"

namespace sjsu::drive{

    struct motor_feedback{
        units::angular_velocity::revolutions_per_minute_t left_hub_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t right_hub_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t back_hub_speed = 0_rpm;
    };

}