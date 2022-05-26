#pragma once
#include "../library/devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"

namespace sjsu::arm
{
    class MpuRouter
    {
        MpuRouter(Mpu6050 &rotunda, Mpu6050 &shoulder, Mpu6050 &elbow, Mpu6050 &wrist) :
        rotunda_(rotunda), shoulder_(shoulder), elbow_(elbow), wrist_(wrist)
        {
            // TODO
        }

        imu_accelerometers_feedback GetFeedback()
        {
            return {};
        }

    private:
        Mpu6050 &rotunda_;
        Mpu6050 &shoulder_;
        Mpu6050 &elbow_;
        Mpu6050 &wrist_;
    };
}
