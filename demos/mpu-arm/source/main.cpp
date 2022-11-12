#include <cstdint>
#include "peripherals/lpc40xx/i2c.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "../../subsystem-arm/implementations/routers/tca9458a-router.hpp"
#include "../../subsystem-arm/implementations/routers/mpu-router.hpp"
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
    sjsu::arm::TCA9458A mux(i2c);
    i2c.Initialize();

    // write to the base accelerometers to open the correct mux bus
    sjsu::LogInfo("Initializing base accelerometers...");
    mux.OpenBus(1);
    sjsu::Mpu6050 rotunda(i2c, 0x68);
    sjsu::Mpu6050 shoulder(i2c, 0x69);
    InitializeBase(rotunda, shoulder);
    
    // write to the join accelerometers to open the correct mux bus
    sjsu::LogInfo("Initializing joint accelerometers...");
    sjsu::Delay(10ms);
    mux.OpenBus(1);
    sjsu::Mpu6050 elbow(i2c, 0x68);
    sjsu::Mpu6050 wrist(i2c, 0x69);
    sjsu::LogInfo("done creating mpus");
    InitializeJoints(elbow, wrist);
    sjsu::Delay(10ms);
    while (true)
    {
        sjsu::LogInfo("Starting main control loop");
        mux.OpenBus(0);
        sjsu::LogInfo("Reading rotunda Mpu6050 acceleration data...");
        PrintAcceleration(rotunda);
        sjsu::LogInfo("Reading shoulder Mpu6050 acceleration data...");
        PrintAcceleration(shoulder);

        mux.OpenBus(1);
        sjsu::LogInfo("Reading elbow Mpu6050 acceleration data...");
        PrintAcceleration(elbow);
        sjsu::LogInfo("Reading wrist Mpu6050 acceleration data...");
        PrintAcceleration(wrist);

    }
    return 0;
}