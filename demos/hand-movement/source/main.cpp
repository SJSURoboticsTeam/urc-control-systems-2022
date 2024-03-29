#include "peripherals/lpc40xx/i2c.hpp"
#include "pca9685.hpp"
#include "arm-dto.hpp"
#include "hand-router.hpp"
#include "mode-select.hpp"

std::chrono::microseconds AngleToPulseWidth(int angle)
{
    return std::chrono::microseconds(angle * (4096 / 360));
}

int main()
{
    // Initializing 12c and pca9685
    // Side Note: Make sure all Servos have enough power to move. the sjtwo doesn't have enough.
    int min_angle = 175; // approximated min angle for pq12-100-servo
    int max_angle = 88;  // approximated max angle for pq12-100-servo
    sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
    sjsu::Pca9685 pca9685(i2c, 0x40);
    sjsu::LogInfo("Initializing PCA...");
    pca9685.ModuleInitialize();
    sjsu::arm::HandRouter hand_router(pca9685);
    sjsu::arm::hand_arguments Hand_Arguments;

    using namespace sjsu::arm;
    while (1)
    {
        // open hand
        Hand_Arguments.thumb_angle = min_angle;
        Hand_Arguments.index_angle = min_angle;
        Hand_Arguments.middle_angle = min_angle;
        Hand_Arguments.ring_angle = min_angle;
        Hand_Arguments.pinky_angle = min_angle;

        sjsu::LogInfo("Finger Open angles: %d, %d, %d, %d, %d", Hand_Arguments.thumb_angle,
                      Hand_Arguments.index_angle, Hand_Arguments.middle_angle,
                      Hand_Arguments.ring_angle, Hand_Arguments.pinky_angle);

        Hand_Arguments.mode = 'C';
        sjsu::LogInfo("Closed Hand Mode");
        Hand_Arguments = ModeSelect::SelectMode(Hand_Arguments);
        hand_router.MoveToAngle(Hand_Arguments);
        sjsu::Delay(5s);

        Hand_Arguments.mode = 'O';
        sjsu::LogInfo("Open Hand Mode");
        Hand_Arguments = ModeSelect::SelectMode(Hand_Arguments);
        hand_router.MoveToAngle(Hand_Arguments);
        sjsu::Delay(5s);

        Hand_Arguments.mode = 'I';
        Hand_Arguments.thumb_angle = 88;
        Hand_Arguments.index_angle = 95;
        Hand_Arguments.middle_angle = 105;
        Hand_Arguments.ring_angle = 120;
        Hand_Arguments.pinky_angle = 150;
        sjsu::LogInfo("Individual Hand Mode");
        Hand_Arguments = ModeSelect::SelectMode(Hand_Arguments);
        hand_router.MoveToAngle(Hand_Arguments);
        sjsu::Delay(5s);

        Hand_Arguments.mode = 'S';
        Hand_Arguments.index_angle = 100;
        sjsu::LogInfo("Simultaneous Hand Mode");
        Hand_Arguments = ModeSelect::SelectMode(Hand_Arguments);
        hand_router.MoveToAngle(Hand_Arguments);
        sjsu::Delay(5s);
    }
    return 0;
}