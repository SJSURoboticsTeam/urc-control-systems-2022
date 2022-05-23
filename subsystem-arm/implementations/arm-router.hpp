#pragma once
#include "../library/devices/actuators/servo/rmd_x.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::arm
{
    class ArmRouter
    {
        public: 
        ArmRouter(sjsu::RmdX & routnda, sjsu::RmdX & shoulder, sjsu::RmdX & elbow, sjsu::RmdX & wrist_pitch, sjsu::RmdX & wrist_yaw){

        }

        void Initialize(){};

        motor_arguments SetArmArguments (motor_arguments arguments)
        {
            //TODO: Set angles for each motor
            return {};
        }

        void HomeArm(imu_accelerometers_feedback mpu_feedback, motors_feedback motors_feedback)
        {

        }
  
        private:
        sjsu::arm::motor_arguments motors;
    };
}
