#include <cstdint>
#include "peripherals/lpc40xx/i2c.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "utility/log.hpp"



void PrintAcceleration(sjsu::Mpu6050 &mpu)
{
    auto current_acceleration = mpu.Read();
    current_acceleration.Print();
}


int main()
{
    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Mpu6050 sensor(i2c, 0x68);
        
    sjsu::LogInfo("Mpu6050 Application Starting...");

    sjsu::LogInfo("Initializing accelerometers...");
    sensor.Initialize();
    while (true)
    {
       
        sjsu::LogInfo("Reading sensor Mpu6050 acceleration data...");
        PrintAcceleration(sensor);

        sjsu::Delay(100ms); 
    }
    return 0;
}