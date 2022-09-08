#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc17xx/pwm.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

int main()
{
    // sjsu::LogInfo("Starting the rover arm system...");
    // sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
    // sjsu::StaticMemoryResource<1024> memory_resource;
    // sjsu::CanNetwork can_network(can, &memory_resource);

    // sjsu::RmdX elbow_motor(can_network, 0x142);

    // elbow_motor.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder

    // // rotunda_motor.Initialize();
    // elbow_motor.Initialize();
    // // left_wrist_motor.Initialize();
    // // right_wrist_motor.Initialize();

    // while (true)
    // {
    //     sjsu::LogInfo("Moving motor...");
    //     elbow_motor.GetFeedback().Print();
    //     auto feedback = elbow_motor.GetFeedback().missed_feedback;
    //     elbow_motor.SetSpeed(5_rpm);
    //     sjsu::Delay(100ms);
    // }

    sjsu::LogInfo("Starting the rover arm system...");
    sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
    sjsu::StaticMemoryResource<1024> memory_resource;
    sjsu::CanNetwork can_network(can, &memory_resource);

    // RMD addresses 0x141 - 0x148 are available
    sjsu::RmdX elbow_motor(can_network, 0x143);
    sjsu::RmdX shoulder_motor(can_network, 0x142);
    sjsu::RmdX wrist_motor(can_network, 0x144);
    sjsu::RmdX wrist_motor2(can_network, 0x145);
    // sjsu::RmdX wrist_motor2(can_network, 0x145);

    // sjsu::RmdX elbow_motor(can_network, 0x143);

    // wrist_motor1.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder
    // wrist_motor2.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder
    elbow_motor.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder

    elbow_motor.Initialize();
    shoulder_motor.Initialize();
    wrist_motor.Initialize();
    wrist_motor2.Initialize();

    while (true)
    {
        sjsu::LogInfo("Moving motors...");

        // elbow_motor.GetFeedback().Print();
        // elbow_motor.SetAngle(-10_deg, 3_rpm);
        // sjsu::Delay(3000ms);
        // shoulder_motor.GetFeedback().Print();
        sjsu::LogInfo("Moving shoulder to 30...");
        shoulder_motor.SetAngle(30_deg, 6_rpm);
        elbow_motor.SetAngle(-30_deg, 2_rpm);
        wrist_motor.SetSpeed(-15_rpm);
        wrist_motor2.SetSpeed(-8_rpm);
        sjsu::Delay(5000ms);
        sjsu::LogInfo("Moving shoulder to 90...");
        shoulder_motor.SetAngle(240_deg, 6_rpm);
        // elbow_motor.SetAngle(-60_deg, 2_rpm);
        wrist_motor.SetSpeed(15_rpm);
        wrist_motor2.SetSpeed(8_rpm);
        sjsu::Delay(5000ms);
        sjsu::LogInfo("Moving shoulder to 180...");
        shoulder_motor.SetAngle(360_deg, 6_rpm);
        // elbow_motor.SetAngle(-90_deg, 2_rpm);
        wrist_motor.SetSpeed(25_rpm);
        wrist_motor2.SetSpeed(12_rpm);
        sjsu::Delay(5000ms);
        // wrist_motor.GetFeedback().Print();
        // wrist_motor.SetSpeed(15_rpm);
        // wrist_motor2.SetSpeed(8_rpm);
        // sjsu::Delay(3000ms);
        // wrist_motor.GetFeedback().Print();
        // wrist_motor.SetSpeed(-15_rpm);
        // wrist_motor2.SetSpeed(-8_rpm);
        // sjsu::Delay(3000ms);
    }

    return 0;
}