#pragma once
#include "utility/log.hpp"
#include "utility/math/units.hpp"
#include "devices/sensors/movement/accelerometer.hpp"

#include "../../dto/arm-dto.hpp"
#include "../../dto/feedback-dto.hpp"
#include "tca9458a-router.hpp"

namespace sjsu::arm
{
    class HomingSystem
    {
        HomingSystem(Accelerometer &rotunda, Accelerometer &shoulder, Accelerometer &elbow, Accelerometer &wrist, TCA9458A &multiplexor ) : rotunda_(rotunda), shoulder_(shoulder), elbow_(elbow), wrist_(wrist), mux_(multiplexor)
        {
            mux_.OpenBus(0);
            rotunda_.ModuleInitialize();
            shoulder_.ModuleInitialize();
            mux_.OpenBus(1);
            elbow_.ModuleInitialize();
            wrist_.ModuleInitialize();
        }

        arm_accelerometer_feedback GetFeedback()
        {
            arm_accelerometer_feedback temp;

            Accelerometer::Acceleration_t rotunda_mpu = rotunda_.Read();
            Accelerometer::Acceleration_t shoulder_mpu = shoulder_.Read();
            mux_.OpenBus(1);
            Accelerometer::Acceleration_t elbow_mpu = elbow_.Read();
            // Accelerometer::Acceleration_t wrist_mpu = wrist_.Read();

            temp.rotunda.x = static_cast<int>(rotunda_mpu.x);
            temp.rotunda.y = static_cast<int>(rotunda_mpu.y);
            temp.rotunda.z = static_cast<int>(rotunda_mpu.z);

            temp.shoulder.x = static_cast<int>(shoulder_mpu.x);
            temp.shoulder.y = static_cast<int>(shoulder_mpu.y);
            temp.shoulder.z = static_cast<int>(shoulder_mpu.z);

            temp.elbow.x = static_cast<int>(elbow_mpu.x);
            temp.elbow.y = static_cast<int>(elbow_mpu.y);
            temp.elbow.z = static_cast<int>(elbow_mpu.z);

            return temp;
        }

    private:
        Accelerometer &rotunda_;
        Accelerometer &shoulder_;
        Accelerometer &elbow_;
        Accelerometer &wrist_;
        TCA9458A &mux_;
    };
}
