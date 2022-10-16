#pragma once
#include "utility/log.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::demo
{
    class Leg
    {
    public:
        Leg(sjsu::RmdX &steer, sjsu::RmdX &drive, sjsu::Gpio &magnet, float offset, std::string name) : steer_motor_(steer), drive_motor_(drive), magnet_(magnet), offset_(offset), name_(name) {}

        void Initialize()
        {
            steer_motor_.Initialize();
            drive_motor_.Initialize();
        }

        void SetSteerAngle(int angle)
        {
            units::angle::degree_t cast_angle = units::angle::degree_t(static_cast<float>(angle));
            steer_motor_.SetAngle(cast_angle);
        }

        void Print()
        {
            sjsu::LogInfo("%s Offset: %f", name_.c_str(), offset_);
        }

        void HomeLeg()
        {
            units::angular_velocity::revolutions_per_minute_t angle_feedback;
            int not_homed = 1;
            while (common::RmdEncoder::CalcEncoderPositions(steer_motor_) != 0)
            {
                steer_motor_.SetAngle(units::angle::degree_t(0), 2_rpm);
            }

            while (magnet_.Read() == not_homed)
            {
                offset_++;
                steer_motor_.SetAngle(units::angle::degree_t(offset_, 3_rpm));
                angle_feedback = steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
                while (steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed != 0_rpm)
                {
                    angle_feedback = steer_motor_.RequestFeedbackFromMotor().GetFeedback().speed;
                }
            }
        }

    private:
        sjsu::RmdX &steer_motor_;
        sjsu::RmdX &drive_motor_;
        sjsu::Gpio &magnet_;
        float offset_;
        std::string name_;
    };
} // namespace sjsu::drive
