#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc17xx/pwm.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

#include "../../common/serial.hpp"
#include "../../common/rmd-encoder.hpp"
#include "rover.hpp"
#include "leg.hpp"

int main()
{
    sjsu::LogInfo("Starting demo application...");
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
    sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
    sjsu::StaticMemoryResource<1024> memory_resource;
    sjsu::CanNetwork can_network(can, &memory_resource);

    // RMD addressesGetSerialCommands 0x141 - 0x148 are available
    sjsu::RmdX left_steer_motor(can_network, 0x141);
    sjsu::RmdX left_hub_motor(can_network, 0x142);
    sjsu::RmdX right_steer_motor(can_network, 0x143);
    sjsu::RmdX right_hub_motor(can_network, 0x144);
    sjsu::RmdX back_steer_motor(can_network, 0x145);
    sjsu::RmdX back_hub_motor(can_network, 0x146);

    left_steer_motor.settings.gear_ratio = 6;
    left_hub_motor.settings.gear_ratio = 15;
    right_steer_motor.settings.gear_ratio = 6;
    right_hub_motor.settings.gear_ratio = 15;
    back_steer_motor.settings.gear_ratio = 6;
    back_hub_motor.settings.gear_ratio = 15;

    auto &left_magnet = sjsu::lpc40xx::GetGpio<2, 1>();
    auto &right_magnet = sjsu::lpc40xx::GetGpio<2, 2>();
    auto &back_magnet = sjsu::lpc40xx::GetGpio<2, 0>();

    left_steer_motor.Initialize();
    right_steer_motor.Initialize();
    back_steer_motor.Initialize();

    left_hub_motor.Initialize();
    right_hub_motor.Initialize();
    back_hub_motor.Initialize();

    float left_steer_encoder_position = sjsu::common::RmdEncoder::CalcEncoderPositions(left_steer_motor);
    float right_steer_encoder_position = sjsu::common::RmdEncoder::CalcEncoderPositions(right_steer_motor);
    float back_steer_encoder_position = sjsu::common::RmdEncoder::CalcEncoderPositions(back_steer_motor);

    sjsu::demo::Leg left_leg(left_steer_motor, left_hub_motor, left_magnet, left_steer_encoder_position, "Left");
    sjsu::demo::Leg right_leg(right_steer_motor, right_hub_motor, right_magnet, right_steer_encoder_position, "Right");
    sjsu::demo::Leg back_leg(back_steer_motor, back_hub_motor, back_magnet, back_steer_encoder_position, "Back");

    sjsu::demo::Rover::Legs legs = {&left_leg, &right_leg, &back_leg};
    sjsu::demo::Rover rover(legs);

    // home rover
    left_leg.HomeLeg();
    right_leg.HomeLeg();
    back_leg.HomeLeg();

    rover.SetLegsToZeroExceptBack(0);
    sjsu::LogInfo("Waiting 3 seconds...");
    sjsu::Delay(3s);
    sjsu::LogInfo("Ready!");

    int wheel_orientation = 0;
    while (true)
    {
        std::string response = serial.GetCommands();
        if (response != "")
        {
            int new_wheel_orientation = std::stoi(response);
            if (new_wheel_orientation != wheel_orientation)
            {
                wheel_orientation = new_wheel_orientation;
                rover.SwitchLegOrientation(wheel_orientation);
            }
        }
        rover.SetLegsToZeroExceptBack(90);
    }

    return 0;
}
