#include "../implementations/hand/pca9685.hpp"
#include "peripherals/lpc40xx/i2c.hpp"

int main()
{

    // Initializing 12c and pca9685
    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Pca9685 pca9685(i2c);
    sjsu::LogInfo("Initializing PCA...");
    pca9685.Initialize();
    pca9685.ModuleInitialize();
    pca9685.setFrequency(60_Hz);
    pca9685.SetDutyCycle(0, 0.2, 0);
    pca9685.SetDutyCycle(1, 0.2, 0);

    while (1)
    {
        sjsu::LogInfo("Testing PCA...");
        //pca9685.fullOn(0);
        //pca9685.fullOn(1);
        pca9685.setPulseWidth(0, 650us);
        pca9685.setPulseWidth(1, 650us);
        sjsu::Delay(2s);
        //pca9685.fullOff(0);
        //pca9685.fullOff(1);
        pca9685.setPulseWidth(0, 2350us);
        pca9685.setPulseWidth(1, 2350us);
    }
    return 0;
}