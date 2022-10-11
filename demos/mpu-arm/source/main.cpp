#include <cstdint>
#include "peripherals/lpc40xx/i2c.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "utility/log.hpp"

void PrintAcceleration(sjsu::Mpu6050 &sensor)
{
    auto current_acceleration = sensor.Read();
    current_acceleration.Print();
}

void InitializeArm( sjsu::Mpu6050 &elbow)
{
    elbow.Initialize();

}

int main()
{
    sjsu::LogInfo("Mpu6050 Application Starting...");

    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Mpu6050 elbow(i2c, 0x68);


    sjsu::LogInfo("Initializing accelerometers...");
    InitializeArm(elbow);

    while (true)
    {

        sjsu::LogInfo("Reading elbow Mpu6050 acceleration data...");
        PrintAcceleration(elbow);


        sjsu::Delay(100ms);
    }
    return 0;
}