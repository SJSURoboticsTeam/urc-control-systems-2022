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
            a_.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.left.steer.angle + initial_encoder_position_a_),
                                     units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.steer.speed));
            a_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.hub.speed));

            c_.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.right.steer.angle + initial_encoder_position_c_),
                                     units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.steer.speed));
            c_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.hub.speed));

            b_.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.back.steer.angle + initial_encoder_position_b_),
                                     units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.back.steer.speed));
            b_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.back.hub.speed));

            tri_wheel_arguments_ = tri_wheel_arguments;
        }

        tri_wheel_router_arguments GetTriWheelRouterArguments() const
        {
            return tri_wheel_arguments_;
        }

        /// At the moment, homing is where the legs turn on so we just calculate the initial encoder positions. ***Must be called in main
        void HomeLegs()
        {
            CalculateInitialEncoderPositions();
        }

    private:

    //auxillary functions

        /// Gets raw data from steer motors, calculates the angles, and sets the initial_encoder_positions.
        void CalculateInitialEncoderPositions()
        {
            initial_encoder_position_b_ = MapEncoderDataToDegrees(b_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_encoder_position_a_ = MapEncoderDataToDegrees(a_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_encoder_position_c_ = MapEncoderDataToDegrees(c_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
        }

        /// takes data from encoder and maps it to degrees
        float MapEncoderDataToDegrees(float encoder_data)
        {
            return (60 * encoder_data / 256);
        }

    //member variables

        float initial_encoder_position_a_ = 0;
        float initial_encoder_position_b_ = 0;
        float initial_encoder_position_c_ = 0;

        leg a_;
        leg b_;
        leg c_;
        tri_wheel_router_arguments tri_wheel_arguments_;
    };
} // namespace sjsu::drive