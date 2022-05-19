#pragma once
#include "../library/devices/actuators/servo/rmd_x.hpp"
#include "../subsystem-drive/dto/drive-dto.hpp"
#include "../subsystem-drive/dto/motor-feedback-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"

namespace sjsu::drive
{
    class TriWheelRouter
    {
    public:
        struct leg
        {
            leg(sjsu::RmdX &steer, sjsu::RmdX &drive) : steer_motor_(steer), drive_motor_(drive)
            {}
            sjsu::RmdX &steer_motor_;
            sjsu::RmdX &drive_motor_;
        };

        TriWheelRouter(leg right, leg left, leg back) : left_(left), back_(back), right_(right)
        {}

        void Initialize()
        {
            left_.steer_motor_.Initialize();
            back_.steer_motor_.Initialize();
            right_.steer_motor_.Initialize();
            left_.drive_motor_.Initialize();
            back_.drive_motor_.Initialize();
            right_.drive_motor_.Initialize();
        }

        tri_wheel_router_arguments SetLegArguments(tri_wheel_router_arguments tri_wheel_arguments)
        {
            left_.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.left.steer.angle - initial_encoder_position_left_),
                                     units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.steer.speed));
            left_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.hub.speed));

            right_.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.right.steer.angle + initial_encoder_position_right_),
                                     units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.steer.speed));
            right_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.hub.speed));

            back_.steer_motor_.SetAngle(units::angle::degree_t(tri_wheel_arguments.back.steer.angle + initial_encoder_position_back_),
                                     units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.back.steer.speed));
            back_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.back.hub.speed));

            tri_wheel_arguments_ = tri_wheel_arguments;
            return tri_wheel_arguments_;
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
        /// Gets raw data from steer motors, calculates the angles, and sets the initial_encoder_positions.
        void CalculateInitialEncoderPositions()
        {
            initial_encoder_position_back_ = MapEncoderDataToDegrees(back_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_encoder_position_left_ = MapEncoderDataToDegrees(left_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
            initial_encoder_position_right_ = MapEncoderDataToDegrees(right_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8);
        }

        motor_feedback GetMotorFeedback(){
            motor_feedback motor_speeds;
            motor_speeds.left_steer_speed = left_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
            motor_speeds.right_steer_speed = right_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
            motor_speeds.back_steer_speed = back_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
            return motor_speeds;
        }

    private:

    //auxillary functions

        /// takes data from encoder and maps it to degrees
        float MapEncoderDataToDegrees(float encoder_data)
        {
            return (60.0 * encoder_data / 256.0);
        }

    //member variables

        float initial_encoder_position_left_ = 0;
        float initial_encoder_position_back_ = 0;
        float initial_encoder_position_right_ = 0;

        leg left_;
        leg back_;
        leg right_;
        tri_wheel_router_arguments tri_wheel_arguments_;
    };
} // namespace sjsu::drive