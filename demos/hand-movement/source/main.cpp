// #include "../pca9685.hpp"
// #include "peripherals/lpc40xx/i2c.hpp"

// std::chrono::microseconds AngleToPulseWidth(int angle)
// {
//     return std::chrono::microseconds(angle * (4096 / 360));
// }

// int main()
// {
//     //Initializing 12c and pca9685
//     //Side Note: Make sure all Servos have enough power to move. the sjtwo doesn't have enough.
//     int min_angle = 88;  // approximated min angle for pq12-100-servo
//     int max_angle = 175; // approximated max angle for pq12-100-servo
//     sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
//     sjsu::Pca9685 pca9685(i2c, 0x40);
//     sjsu::LogInfo("Initializing PCA...");
//     pca9685.ModuleInitialize();

//     while (1)
//     {
//         sjsu::LogInfo("Open Hand");
//         pca9685.setPulseWidth(0, AngleToPulseWidth(min_angle)); //pinky
//         pca9685.setPulseWidth(1, AngleToPulseWidth(min_angle)); //ring
//         pca9685.setPulseWidth(2, AngleToPulseWidth(min_angle)); //middle
//         pca9685.setPulseWidth(3, AngleToPulseWidth(min_angle)); //index
//         pca9685.setPulseWidth(4, AngleToPulseWidth(min_angle)); //thumb
//         sjsu::Delay(2s);
//         sjsu::LogInfo("Closed Hand");
//         pca9685.setPulseWidth(0, AngleToPulseWidth(max_angle)); //pinky
//         pca9685.setPulseWidth(1, AngleToPulseWidth(max_angle)); //ring
//         pca9685.setPulseWidth(2, AngleToPulseWidth(max_angle)); //middle
//         pca9685.setPulseWidth(3, AngleToPulseWidth(max_angle)); //index
//         pca9685.setPulseWidth(4, AngleToPulseWidth(max_angle)); //thumb
//         sjsu::Delay(2s);
//     }
//     return 0;
// }
#include "peripherals/lpc40xx/i2c.hpp"
#include "../hand-router.hpp"
#include "../arm-dto.hpp"


std::chrono::microseconds AngleToPulseWidth(int angle)
{
    return std::chrono::microseconds(angle * (4096 / 360));
}

int main()
{
    //Initializing 12c and pca9685
    //Side Note: Make sure all Servos have enough power to move. the sjtwo doesn't have enough.
    int min_angle = 30;  // approximated min angle for pq12-100-servo
    int max_angle = 88; // approximated max angle for pq12-100-servo
    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Pca9685 pca9685(i2c, 0x40);
    sjsu::LogInfo("Initializing PCA...");
    pca9685.ModuleInitialize();
    sjsu::arm::HandRouter hand_router(pca9685);
    sjsu::arm::hand_arguments Hand_Arguments;

    while (1)
    {
        Hand_Arguments.thumb_angle = max_angle;
        Hand_Arguments.index_angle = max_angle;
        Hand_Arguments.middle_angle = max_angle;
        Hand_Arguments.ring_angle = max_angle;
        Hand_Arguments.pinky_angle = max_angle;

        sjsu::LogInfo("Open Hand");
        hand_router.MoveToAngle(Hand_Arguments);
        sjsu::Delay(2s);
        sjsu::LogInfo("Closed Hand");
        hand_router.MoveToAngle(Hand_Arguments);
        sjsu::Delay(2s);
    }
    return 0;
}