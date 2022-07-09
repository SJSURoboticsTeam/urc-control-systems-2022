#include "../pca9685.hpp"
#include "peripherals/lpc40xx/i2c.hpp"

std::chrono::microseconds AngleToPulseWidth(int angle)
{
    return std::chrono::microseconds(angle * (4096 / 360));
}

int main()
{
    // Initializing 12c and pca9685
    int angle1 = 30;  // min angle for SG90 9G Micro Servo
    int angle2 = 180; // max angle for SG90 9G Micro Servo
    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Pca9685 pca9685(i2c, 0x40);
    sjsu::LogInfo("Initializing PCA...");
    pca9685.ModuleInitialize();

    while (1)
    {
        sjsu::LogInfo("Moving to first angle: %d", angle1);
        pca9685.setPulseWidth(0, AngleToPulseWidth(angle1));
        pca9685.setPulseWidth(1, AngleToPulseWidth(angle1));
        sjsu::Delay(2s);
        sjsu::LogInfo("Moving to second angle: %d", angle2);
        pca9685.setPulseWidth(0, AngleToPulseWidth(angle2));
        pca9685.setPulseWidth(1, AngleToPulseWidth(angle2));
        sjsu::Delay(2s);
    }
    return 0;
}