#include <cstdint>
#include "peripherals/lpc40xx/i2c.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "utility/log.hpp"

void PrintAcceleration(sjsu::Mpu6050 &sensor)
{
    auto current_acceleration = sensor.Read();
    current_acceleration.Print();
}

void InitializeArm(sjsu::Mpu6050 &rotunda, sjsu::Mpu6050 &shoulder, sjsu::Mpu6050 &elbow, sjsu::Mpu6050 &wrist)
{
    rotunda.Initialize();
    shoulder.Initialize();
    elbow.Initialize();
    wrist.Initialize();
}

int main()
{
    sjsu::LogInfo("Mpu6050 Application Starting...");

    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Mpu6050 rotunda(i2c, 0x66);
    sjsu::Mpu6050 shoulder(i2c, 0x67);
    sjsu::Mpu6050 elbow(i2c, 0x68);
    sjsu::Mpu6050 wrist(i2c, 0x69);

    sjsu::LogInfo("Initializing accelerometers...");
    InitializeArm(rotunda, shoulder, elbow, wrist);

    while (true)
    {
        sjsu::LogInfo("Reading rotunda Mpu6050 acceleration data...");
        PrintAcceleration(rotunda);
        sjsu::LogInfo("Reading shoulder Mpu6050 acceleration data...");
        PrintAcceleration(shoulder);
        sjsu::LogInfo("Reading elbow Mpu6050 acceleration data...");
        PrintAcceleration(elbow);
        sjsu::LogInfo("Reading wrist Mpu6050 acceleration data...");
        PrintAcceleration(wrist);

        sjsu::Delay(100ms);
    }
    return 0;
}