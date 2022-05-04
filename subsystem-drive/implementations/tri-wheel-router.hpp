#pragma once
#include "SJSU-Dev2/library/devices/actuators/servo/rmd_x.hpp"
#include "urc-control-systems-2022/subsystem-drive/dto/drive-dto.hpp"
#include "utility/math/units.hpp"

namespace sjsu::drive
{
    class TriWheelRouter
    {
    public:
        struct leg
        {
            sjsu::RmdX &steer_motor_;
            sjsu::RmdX &drive_motor_;
        };

        TriWheelRouter();

        void SetLegArguments(tri_wheel_router_arguments tri_wheel_arguments)
        {
            tri_wheel_arguments_ = tri_wheel_arguments;
            a.steer_motor_.SetAngle(static_cast<units::angle::degree_t>(tri_wheel_arguments.a.steer.angle));
            a.steer_motor_.SetSpeed(static_cast<units::angular_velocity::revolutions_per_minute_t>(tri_wheel_arguments.a.steer.speed));
            a.drive_motor_.SetSpeed(static_cast<units::angular_velocity::revolutions_per_minute_t>(tri_wheel_arguments.a.hub.speed));
            b.steer_motor_.SetAngle(static_cast<units::angle::degree_t>(tri_wheel_arguments.b.steer.angle));
            b.steer_motor_.SetSpeed(static_cast<units::angular_velocity::revolutions_per_minute_t>(tri_wheel_arguments.b.steer.speed));
            b.drive_motor_.SetSpeed(static_cast<units::angular_velocity::revolutions_per_minute_t>(tri_wheel_arguments.b.hub.speed));
            c.steer_motor_.SetAngle(static_cast<units::angle::degree_t>(tri_wheel_arguments.c.steer.angle));
            c.steer_motor_.SetSpeed(static_cast<units::angular_velocity::revolutions_per_minute_t>(tri_wheel_arguments.c.steer.speed));
            c.drive_motor_.SetSpeed(static_cast<units::angular_velocity::revolutions_per_minute_t>(tri_wheel_arguments.c.hub.speed));
        }

        tri_wheel_router_arguments GetTriWheelRouterArguments()
        {
            return tri_wheel_arguments_;
        }

    private:
        leg a;
        leg b;
        leg c;
        tri_wheel_router_arguments tri_wheel_arguments_;
    };
} // namespace sjsu::drive