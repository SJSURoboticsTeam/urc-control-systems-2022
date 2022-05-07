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
            left.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.left.steer.angle),
                                       units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.steer.speed));
            left.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.hub.speed));

            right.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.right.steer.angle),
                                        units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.steer.speed));
            right.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.hub.speed));

            back.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.back.steer.angle),
                                       units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.back.steer.speed));
            back.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.back.hub.speed));

            tri_wheel_arguments_ = tri_wheel_arguments;
        }

        tri_wheel_router_arguments GetTriWheelRouterArguments() const
        {
            return tri_wheel_arguments_;
        }

    private:
        leg a_;
        leg b_;
        leg c_;
        tri_wheel_router_arguments tri_wheel_arguments_;
    };
} // namespace sjsu::drive