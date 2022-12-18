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

            temp.rotunda.x = rotunda_mpu.x.to<double>();
            temp.rotunda.y = rotunda_mpu.y.to<double>();
            temp.rotunda.z = rotunda_mpu.z.to<double>();

            temp.elbow.x = elbow_mpu.x.to<double>();
            temp.elbow.y = elbow_mpu.y.to<double>();
            temp.elbow.z = elbow_mpu.z.to<double>();

            temp.shoulder.x = shoulder_mpu.x.to<double>();
            temp.shoulder.y = shoulder_mpu.y.to<double>();
            temp.shoulder.z = shoulder_mpu.z.to<double>();

            temp.wrist.x = wrist_mpu.x.to<double>();
            temp.wrist.y = wrist_mpu.y.to<double>();
            temp.wrist.z = wrist_mpu.z.to<double>();

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
