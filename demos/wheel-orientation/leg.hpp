#pragma once
#include "utility/log.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::demo
{
    class Leg
    {
    public:
        Leg(sjsu::RmdX &steer, sjsu::RmdX &drive, int offset, std::string name) : steer_motor_(steer), drive_motor_(drive), offset_(offset), name_(name) {}

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
            sjsu::LogInfo("%s Offset: %d", name_.c_str(), offset_);
        }

    private:
        sjsu::RmdX &steer_motor_;
        sjsu::RmdX &drive_motor_;
        int offset_;
        std::string name_;
    };
} // namespace sjsu::drive
