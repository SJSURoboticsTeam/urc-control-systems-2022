#include <cstdint>
#include "peripherals/lpc40xx/i2c.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "../../subsystem-arm/implementations/routers/tca9458a-router.hpp"
#include "../../subsystem-arm/implementations/routers/mpu-router.hpp"
#include "../../subsystem-arm/implementations/routers/joint-router.hpp"
#include "utility/log.hpp"
#include "peripherals/lpc40xx/can.hpp"

#include "math.h"



void PrintAcceleration(sjsu::Mpu6050 &mpu)
{
    auto current_acceleration = mpu.Read();
    current_acceleration.Print();
}



int main()
{
    sjsu::LogInfo("Mpu6050 Application Starting...");
    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::arm::TCA9458A mux(i2c);
    i2c.Initialize();
    
    // write to the base accelerometers to open the correct mux bus
    sjsu::LogInfo("Initializing base accelerometers...");
    mux.OpenBus(0);
    sjsu::Mpu6050 rotunda(i2c, 0x68);
    sjsu::Mpu6050 shoulder(i2c, 0x69);
    mux.OpenBus(1);
    sjsu::Mpu6050 elbow(i2c, 0x68);
    sjsu::Mpu6050 wrist(i2c, 0x69);
    sjsu::arm::HomingSystem quadmpu(rotunda, shoulder, elbow, wrist, mux);
    quadmpu.Initialize();
    sjsu::LogInfo("done creating mpus");
    sjsu::arm::arm_accelerometer_feedback read;
    
    sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
    sjsu::StaticMemoryResource<1024> memory_resource;
    sjsu::CanNetwork can_network(can, &memory_resource);
    
    sjsu::arm::arm_arguments arguement;
    sjsu::RmdX rotunda_motor(can_network, 0x146);
    sjsu::RmdX shoulder_motor(can_network, 0x142);
    sjsu::RmdX elbow_motor(can_network, 0x148);
    sjsu::RmdX left_wrist_motor(can_network, 0x144);
    sjsu::RmdX right_wrist_motor(can_network, 0x145);
    sjsu::arm::JointRouter router(rotunda_motor,shoulder_motor,elbow_motor,left_wrist_motor,right_wrist_motor);
    router.Initialize();

    
    while (true)
    {
        //mpu readings here
        read = quadmpu.GetFeedback();
        read.Print();
        sjsu::Delay(1s);
        //math stuff here
        int rotunda_offset = static_cast<int>(atan2(read.rotunda.x,read.rotunda.z)* 180 / 3.14) ;
        int shoulder_offset = static_cast<int>(atan2(read.shoulder.x,read.shoulder.z) * 180 / 3.14);
        int elbow_offset = static_cast<int>(atan2(read.elbow.x,read.elbow.z) * 180 / 3.14) ;
        sjsu::LogInfo("Rotunda offset: %d,  Shoulder offset: %d,  Elbow offset: %d  ", rotunda_offset, shoulder_offset, elbow_offset);
        arguement.joint_args.shoulder_angle = shoulder_offset + rotunda_offset;
        arguement.joint_args.elbow_angle = elbow_offset + rotunda_offset;
        //move the arm here        
        // arguement.joint_args = router.SetJointArguments(arguement.joint_args);
        arguement.Print();
        sjsu::Delay(5s);
    }
    return 0;
}