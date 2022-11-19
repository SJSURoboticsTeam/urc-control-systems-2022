#pragma once
#include "utility/log.hpp"
#include "utility/math/units.hpp"
#include "peripherals/lpc40xx/gpio.hpp"

#include "../common/rmd-encoder.hpp"
#include "../subsystem-drive/dto/drive-dto.hpp"
#include "../subsystem-drive/dto/motor-feedback-dto.hpp"
#include "../library/devices/actuators/servo/rmd_x.hpp"

namespace sjsu::drive
{
    class TriWheelRouter
    {
    public:
        struct leg
        {
            leg(sjsu::RmdX &steer, sjsu::RmdX &drive, sjsu::Gpio &magnet) : steer_motor_(steer), drive_motor_(drive), magnet_(magnet)
            {
            }
            sjsu::RmdX &steer_motor_;
            sjsu::RmdX &drive_motor_;
            sjsu::Gpio &magnet_;
            int16_t wheel_offset_;
        };

        TriWheelRouter(leg right, leg left, leg back) : left_(left), back_(back), right_(right)
        {
        }

        void Initialize()
        {
            left_.steer_motor_.Initialize();
            back_.steer_motor_.Initialize();
            right_.steer_motor_.Initialize();
            left_.drive_motor_.Initialize();
            back_.drive_motor_.Initialize();
            right_.drive_motor_.Initialize();
            left_.magnet_.Initialize();
            right_.magnet_.Initialize();
            back_.magnet_.Initialize();
            left_.magnet_.SetAsInput();
            right_.magnet_.SetAsInput();
            back_.magnet_.SetAsInput();
            left_.wheel_offset_ = 0;
            right_.wheel_offset_ = 0;
            back_.wheel_offset_ = 0;
        }

        tri_wheel_router_arguments SetLegArguments(tri_wheel_router_arguments tri_wheel_arguments)
        {
            left_.steer_motor_.SetAngle(units::angle::degree_t(-tri_wheel_arguments.left.steer.angle + left_.wheel_offset_),
                                        units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.steer.speed));
            left_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.left.hub.speed));

            right_.steer_motor_.SetAngle(units::angle::degree_t(-tri_wheel_arguments.right.steer.angle + right_.wheel_offset_),
                                         units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.steer.speed));
            right_.drive_motor_.SetSpeed(units::angular_velocity::revolutions_per_minute_t(tri_wheel_arguments.right.hub.speed));

            back_.steer_motor_.SetAngle(units::angle::degree_t(-tri_wheel_arguments.back.steer.angle + back_.wheel_offset_),
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
            motor_feedback angle_verification;

            while (WheelNotZeroDoThis(left_) | WheelNotZeroDoThis(right_) | WheelNotZeroDoThis(back_))
            {
                //This loops until all of the wheels are zeroed and/or homed
            }

            int not_homed = 1;
            bool leftHome = !(left_.magnet_.Read() == not_homed), rightHome = !(right_.magnet_.Read() == not_homed), backHome = !(back_.magnet_.Read() == not_homed);
            
            while((leftHome && WheelNotNeg60DoThis(left_)) | (rightHome && WheelNotNeg60DoThis(right_)) | (backHome && WheelNotNeg60DoThis(back_))  ) {}

            while (WheelNotHomeDoThis(left_) | WheelNotHomeDoThis(right_) | WheelNotHomeDoThis(back_))
            {
                sjsu::LogInfo("HomingPins L = %d\t R = %d\t B = %d", left_.magnet_.Read(), right_.magnet_.Read(), back_.magnet_.Read()); //sigma

                sjsu::LogInfo("b = %d\tr = %d\tl = %d", back_.wheel_offset_, right_.wheel_offset_, left_.wheel_offset_);

                angle_verification = GetMotorFeedback();
                while (angle_verification.left_steer_speed != 0_rpm || angle_verification.right_steer_speed != 0_rpm || angle_verification.back_steer_speed != 0_rpm)
                {
                    angle_verification = GetMotorFeedback();
                }
            }
        }

        motor_feedback GetMotorFeedback()
        {
            motor_feedback motor_speeds;
            motor_speeds.left_steer_speed = left_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
            motor_speeds.right_steer_speed = right_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
            motor_speeds.back_steer_speed = back_.steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
            return motor_speeds;
        }

    private:
        bool WheelNotZeroDoThis(leg& leg_) {
            //This leg is NOT at zero
            if ((common::RmdEncoder::CalcEncoderPositions(leg_.steer_motor_) >= 0.01f) ||  common::RmdEncoder::CalcEncoderPositions(leg_.steer_motor_) <= -0.01f) 
            {
                leg_.steer_motor_.SetAngle(0_deg, 2_rpm);
                //This wheel is NOT at zero
                return true;
            }
            else
            {
                //This wheel is at zero
                return false;
            }
        }

        bool WheelNotNeg60DoThis(leg& leg_) {
            //This leg is NOT at zero
            leg_.wheel_offset_ = 300;
            if ((common::RmdEncoder::CalcEncoderPositions(leg_.steer_motor_) >= 0.01f) ||  common::RmdEncoder::CalcEncoderPositions(leg_.steer_motor_) <= -0.01f) 
            {
                leg_.steer_motor_.SetAngle(-60_deg, 2_rpm);
                //This wheel is NOT at -60
                return true;
            }
            else
            {
                //This wheel is at -60
                return false;
            }
        }

        bool WheelNotHomeDoThis (leg& leg_) {
            int not_homed = 1;

            if (leg_.magnet_.Read() == not_homed)
            {
                leg_.wheel_offset_++;
                leg_.steer_motor_.SetAngle(units::angle::degree_t(leg_.wheel_offset_, 2_rpm));
                return true;
            }
            else 
            {
            return false;
            }
        }

        // member variables

        leg left_;
        leg back_;
        leg right_;
        tri_wheel_router_arguments tri_wheel_arguments_;
    };
} // namespace sjsu::drive