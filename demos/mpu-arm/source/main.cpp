#include <cstdint>
#include <algorithm>

#include "devices/actuators/servo/rmd_x.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "utility/log.hpp"



void PrintAcceleration(sjsu::Mpu6050 &mpu)
{
    auto current_acceleration = mpu.Read();
    current_acceleration.Print();
}

void InitializeBase(sjsu::Mpu6050 &rotunda, sjsu::Mpu6050 &shoulder)
{
    rotunda.Initialize();
    shoulder.Initialize();
}

void InitializeJoints(sjsu::Mpu6050 &elbow, sjsu::Mpu6050 &wrist)
{
    wrist.Initialize();
    sjsu::LogInfo("Wrist initalized");
    elbow.Initialize();
}

int main()
{
    sjsu::LogInfo("Mpu6050 Application Starting...");

    sjsu::lpc40xx::I2c &i2c1 = sjsu::lpc40xx::GetI2c<1>();
    sjsu::lpc40xx::I2c &i2c2 = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Mpu6050 rotunda(i2c1, 0x68);
    sjsu::Mpu6050 shoulder(i2c1, 0x69);
    sjsu::Mpu6050 elbow(i2c2, 0x68);
    sjsu::Mpu6050 wrist(i2c2, 0x69);
    
    elbow.Initialize();
    wrist.Initialize();
    sjsu::LogInfo("I2C2 init");
    rotunda.Initialize();
    shoulder.Initialize();
    sjsu::LogInfo("I2C1/0 init");
    
 

    sjsu::LogInfo("done creating mpus");
    while (true)
    {
        sjsu::LogInfo("Starting main control loop");
        sjsu::LogInfo("Reading rotunda Mpu6050 acceleration data...");
        PrintAcceleration(rotunda);
        sjsu::LogInfo("Reading shoulder Mpu6050 acceleration data...");
        PrintAcceleration(shoulder);
        sjsu::LogInfo("Reading elbow Mpu6050 acceleration data...");
        PrintAcceleration(elbow);
        sjsu::LogInfo("Reading wrist Mpu6050 acceleration data...");
        PrintAcceleration(wrist);

        sjsu::Delay(1s);
    }
    return 0;
}