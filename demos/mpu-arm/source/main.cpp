#include <cstdint>
#include "peripherals/lpc40xx/i2c.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "utility/log.hpp"

void PrintAcceleration(sjsu::Mpu6050 &mpu)
{
    auto current_acceleration = mpu.Read();
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
    uint8_t buff[1] = {0};

    sjsu::Mpu6050 rotunda(i2c, 0x68);
    sjsu::Mpu6050 shoulder(i2c, 0x68);
    sjsu::Mpu6050 elbow(i2c, 0x68);
    sjsu::Mpu6050 wrist(i2c, 0x68);

    sjsu::LogInfo("Initializing accelerometers...");
    InitializeArm(rotunda, shoulder, elbow, wrist);
    while (true)
    {
        buff[0] = 1;
        i2c.Write(0x70, buff, 1); // set [00000001]
        sjsu::LogInfo("Reading rotunda Mpu6050 acceleration data...");
        PrintAcceleration(rotunda);

        buff[0] = static_cast<uint8_t>(buff[0] << 1);
        i2c.Write(0x70, buff, 1); // set [00000010]
        sjsu::LogInfo("Reading shoulder Mpu6050 acceleration data...");
        PrintAcceleration(shoulder);

        buff[0] = static_cast<uint8_t>(buff[0] << 1);
        i2c.Write(0x70, buff, 1); // set [00000100]
        sjsu::LogInfo("Reading elbow Mpu6050 acceleration data...");
        PrintAcceleration(elbow);
        
        buff[0] = static_cast<uint8_t>(buff[0] << 1); 
        i2c.Write(0x70, buff, 1); // set [00001000]
        sjsu::LogInfo("Reading wrist Mpu6050 acceleration data...");
        PrintAcceleration(wrist);

        sjsu::Delay(100ms);
    }
    return 0;
}