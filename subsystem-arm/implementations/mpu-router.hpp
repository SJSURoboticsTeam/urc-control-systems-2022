#pragma once
#include "../library/devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "../subsystem-arm/dto/arm-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"

namespace sjsu::arm
{
    class MpuRouter
    {
        MpuRouter(Mpu6050 &rotunda, Mpu6050 &shoulder, Mpu6050 &elbow, Mpu6050 &wrist) : rotunda_(rotunda), shoulder_(shoulder), elbow_(elbow), wrist_(wrist)
        {
            // TODO
        }

        void InitializeAcclerometer()
        {
            rotunda_.ModuleInitialize();
            shoulder_.ModuleInitialize();
            elbow_.ModuleInitialize();
            wrist_.ModuleInitialize();
        }

        imu_accelerometers_feedback GetFeedback()
        {
            imu_accelerometers_feedback temp;

            Accelerometer::Acceleration_t rotunda_mpu = rotunda_.Read();
            Accelerometer::Acceleration_t shoulder_mpu = shoulder_.Read();
            Accelerometer::Acceleration_t elbow_mpu = elbow_.Read();
            Accelerometer::Acceleration_t wrist_mpu = wrist_.Read();

            temp.rotunda.x = static_cast<int>(rotunda_mpu.x);
            temp.rotunda.y = static_cast<int>(rotunda_mpu.y);
            temp.rotunda.z = static_cast<int>(rotunda_mpu.z);

            temp.shoulder.x = static_cast<int>(shoulder_mpu.x);
            temp.shoulder.y = static_cast<int>(shoulder_mpu.y);
            temp.shoulder.z = static_cast<int>(shoulder_mpu.z);

            temp.elbow.x = static_cast<int>(elbow_mpu.x);
            temp.elbow.y = static_cast<int>(elbow_mpu.y);
            temp.elbow.z = static_cast<int>(elbow_mpu.z);

            temp.wrist.x = static_cast<int>(wrist_mpu.x);
            temp.wrist.y = static_cast<int>(wrist_mpu.y);
            temp.wrist.z = static_cast<int>(wrist_mpu.z);

            return temp;
        }

    private:
        Mpu6050 &rotunda_;
        Mpu6050 &shoulder_;
        Mpu6050 &elbow_;
        Mpu6050 &wrist_;
    };
}
