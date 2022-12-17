#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc17xx/pwm.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

int main()
{
    sjsu::LogInfo("Starting the rover arm system...");
    sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<2>();
    sjsu::StaticMemoryResource<1024> memory_resource;
    sjsu::CanNetwork can_network(can, &memory_resource);

    // RMD addresses 0x141 - 0x148 are available
    sjsu::RmdX shoulder_motor(can_network, 0x144);
    // sjsu::RmdX elbow_motor(can_network, 0x143);
    // sjsu::RmdX left_wrist_motor(can_network, 0x144);
    // sjsu::RmdX right_wrist_motor(can_network, 0x145);

    // wrist_motor1.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder
    // right_wrist_motor.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder
    // elbow_motor.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder

    // elbow_motor.Initialize();
    shoulder_motor.Initialize();
    // left_wrist_motor.Initialize();
    // right_wrist_motor.Initialize();

    while (true)
    {
        sjsu::LogInfo("1. Moving shoulder, elbow, left wrist, and right wrist...");
        shoulder_motor.SetAngle(30_deg, 6_rpm);
        // elbow_motor.SetAngle(-30_deg, 2_rpm);
        // left_wrist_motor.SetSpeed(-15_rpm);
        // right_wrist_motor.SetSpeed(-8_rpm);
        sjsu::Delay(2500ms);

        sjsu::LogInfo("2. Moving shoulder, elbow, left wrist, and right wrist...");
        shoulder_motor.SetAngle(240_deg, 6_rpm);
        // elbow_motor.SetAngle(-60_deg, 2_rpm);
        // wrist_motor.SetSpeed(15_rpm);
        // right_wrist_motor.SetSpeed(8_rpm);
        sjsu::Delay(2500ms);

        sjsu::LogInfo("3. Moving shoulder, left wrist, and right wrist...");
        shoulder_motor.SetAngle(360_deg, 6_rpm);
        // wrist_motor.SetSpeed(25_rpm);
        // right_wrist_motor.SetSpeed(12_rpm);
        sjsu::Delay(2500ms);
    }

    return 0;
}