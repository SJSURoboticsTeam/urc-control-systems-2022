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
    public:
        HomingSystem(sjsu::Mpu6050 &rotunda, sjsu::Mpu6050 &shoulder, sjsu::Mpu6050 &elbow, sjsu::Mpu6050 &wrist, TCA9458A &multiplexor ) : rotunda_(rotunda), shoulder_(shoulder), elbow_(elbow), wrist_(wrist), mux_(multiplexor)
        {
            
        }
        void Initialize(){
            mux_.OpenBus(0);
            rotunda_.Initialize();
            shoulder_.Initialize();
            mux_.OpenBus(1);
            elbow_.Initialize();
            wrist_.Initialize();
        }
        arm_accelerometer_feedback GetFeedback()
        {
            arm_accelerometer_feedback temp;
            mux_.OpenBus(0);
            sjsu::Accelerometer::Acceleration_t rotunda_mpu = rotunda_.Read();
            // rotunda_mpu.Print();
            sjsu::Accelerometer::Acceleration_t shoulder_mpu = shoulder_.Read();
            // shoulder_mpu.Print();
            mux_.OpenBus(1);
            sjsu::Accelerometer::Acceleration_t elbow_mpu = elbow_.Read();
            // elbow_mpu.Print();
            sjsu::Accelerometer::Acceleration_t wrist_mpu = wrist_.Read();
            // wrist_mpu.Print();
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
<<<<<<< HEAD
        
        Mpu6050 &rotunda_;
        Mpu6050 &shoulder_;
        Mpu6050 &elbow_;
        Mpu6050 &wrist_;
=======
        Accelerometer &rotunda_;
        Accelerometer &shoulder_;
        Accelerometer &elbow_;
        Accelerometer &wrist_;
>>>>>>> 6c2cf48f4db846f340cb922102173bd48a2e8683
        TCA9458A &mux_;
    };
}
