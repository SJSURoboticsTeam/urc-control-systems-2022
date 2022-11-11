#include <cstdint>
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

    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    uint8_t buff[1] = {1};
    i2c.Initialize();
    
    // write to the base accelerometers to open the correct mux bus
    sjsu::LogInfo("Initializing base accelerometers...");
    i2c.Write(0x70, buff, 1);
    sjsu::Mpu6050 rotunda(i2c, 0x68);
    sjsu::Mpu6050 shoulder(i2c, 0x69);
    InitializeBase(rotunda, shoulder);
    
    // write to the join accelerometers to open the correct mux bus
    sjsu::LogInfo("Initializing joint accelerometers...");
    sjsu::Delay(10ms);
    buff[0] = static_cast<uint8_t>(buff[0] << 1);
    i2c.Write(0x70, buff, 1);
    sjsu::Mpu6050 elbow(i2c, 0x68);
    sjsu::Mpu6050 wrist(i2c, 0x69);
    sjsu::LogInfo("done creating mpus");
    InitializeJoints(elbow, wrist);
    sjsu::Delay(10ms);
    while (true)
    {
        sjsu::LogInfo("Starting main control loop");
        buff[0] = 1;
        i2c.Write(0x70, buff, 1); // set [00000001]
        sjsu::LogInfo("Reading rotunda Mpu6050 acceleration data...");
        PrintAcceleration(rotunda);
        sjsu::Delay(10ms);
        sjsu::LogInfo("Reading shoulder Mpu6050 acceleration data...");
        PrintAcceleration(shoulder);
        sjsu::Delay(10ms);

        buff[0] = static_cast<uint8_t>(buff[0] << 1);
        i2c.Write(0x70, buff, 1); // set [00000010]
        sjsu::LogInfo("Reading elbow Mpu6050 acceleration data...");
        PrintAcceleration(elbow);
        sjsu::Delay(10ms);
        sjsu::LogInfo("Reading wrist Mpu6050 acceleration data...");
        PrintAcceleration(wrist);

        sjsu::Delay(10ms);
    }
    return 0;
}