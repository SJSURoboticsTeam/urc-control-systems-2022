#include "utility/log.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "devices/actuators/servo/rmd_x.hpp"

#include "../implementations/steer-modes.hpp"
#include "../implementations/tri-wheel-router.hpp"
#include "../implementations/mode-switcher.hpp"
#include "../implementations/mode-select.hpp"
#include "../implementations/command-lerper.hpp"

using namespace sjsu::drive;

drive_commands SerialEnterCommands()
{
    drive_commands commands;
    sjsu::LogInfo("Enter in commands");
    scanf("%d,%d,%c", &commands.speed, &commands.angle, &commands.mode);
    return commands;
}

int main()
{
    sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
    sjsu::StaticMemoryResource<1024> memory_resource;
    sjsu::CanNetwork can_network(can, &memory_resource);

    // RMD addresses 0x141 - 0x148 are available
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

    TriWheelRouter::leg right(right_steer_motor, right_hub_motor);
    TriWheelRouter::leg left(left_steer_motor, left_hub_motor);
    TriWheelRouter::leg back(back_steer_motor, back_hub_motor);

    drive_commands commands;
    tri_wheel_router_arguments arguments;
    TriWheelRouter tri_wheel{right, left, back};
    ModeSwitch mode_switch;
    CommandLerper lerp;
    tri_wheel.Initialize();
    tri_wheel.HomeLegs();
    sjsu::Delay(1s);
    while (1)
    {
        // commands = SerialEnterCommands();
        commands.Print();
        sjsu::Delay(1s);
        
        commands.speed = 100;
        if(arguments.back.hub.speed > 50)
        {
            commands.mode = 'S';
        }
        arguments = tri_wheel.SetLegArguments(ModeSelect::SelectMode(lerp.Lerp(mode_switch.SwitchSteerMode(commands, arguments))));
        arguments.Print();

        sjsu::Delay(1s);
    }

    return 0;
}