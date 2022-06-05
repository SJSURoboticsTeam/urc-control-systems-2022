#pragma once
#include "../library/devices/sensors/movement/accelerometer.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"

namespace sjsu::arm
{
    class MpuRouter
    {
        MpuRouter(Accelerometer &rotunda, Accelerometer &shoulder, Accelerometer &elbow, Accelerometer &wrist) :
        rotunda_(rotunda), shoulder_(shoulder), elbow_(elbow), wrist_(wrist)
        {
            // TODO
        }

        imu_accelerometers_feedback GetFeedback()
        {
            return {};
        }

    private:
        Accelerometer &rotunda_;
        Accelerometer &shoulder_;
        Accelerometer &elbow_;
        Accelerometer &wrist_;
    };
}
