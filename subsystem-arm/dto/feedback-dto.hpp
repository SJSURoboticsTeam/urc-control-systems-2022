#pragma once
#include "utility/math/units.hpp"

namespace sjsu::arm{    
    struct accelerometer_feedback
    {
        double x = 0;
        double y = 0;
        double z = 0;
        void Print()
        {
            sjsu::LogInfo("X: %.4f,   Y: %.4f,  Z: %.4f", x, y,z);
        }
    };
    
    struct arm_accelerometer_feedback
    {
        accelerometer_feedback rotunda{};
        accelerometer_feedback shoulder{};
        accelerometer_feedback elbow{};
        accelerometer_feedback wrist{}; 

        void Print()
        {
            sjsu::LogInfo("Rotunda: ");
            rotunda.Print();
            sjsu::LogInfo("Shoulder: ");
            shoulder.Print();
            sjsu::LogInfo("Elbow: ");
            elbow.Print();
            sjsu::LogInfo("Wrist: ");
            wrist.Print();
        }
    };
    
    struct motors_feedback
    {
        units::angular_velocity::revolutions_per_minute_t rotunda_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t shoulder_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t elbow_speed = 0_rpm;
        units::angular_velocity::revolutions_per_minute_t wrist_speed = 0_rpm;
        units::angle::degree_t  rotunda_angle = 0_deg;
        units::angle::degree_t  shoulder_angle = 0_deg;
        units::angle::degree_t  elbow_angle = 0_deg;
        units::angle::degree_t  wrist_angle = 0_deg;
        
        void Print()
        {}
    };
}