#pragma once
#include "library/devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"

namespace sjsu::arm
{
    class MpuRouter
    {
        MpuRouter(Mpu6050 &routnda, Mpu6050 &shoulder, Mpu6050 &elbow, Mpu6050 &wrist){
            //TODO
        }

        imu_accelerometers_feedback GetFeedback(){
            return {};
        }
    }
}
