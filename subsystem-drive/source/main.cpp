#include "utility/log.hpp"

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
    scanf("%d,%d", &commands.speed, &commands.angle);
    return commands;
}

int main()
{
    drive_commands commands;
    tri_wheel_router_arguments arguments;
    SteerModes steermode;
    TriWheelRouter tri_wheel;
    ModeSwitch mode_switch;
    CommandLerper lerp;
    while (1)
    {
        commands = SerialEnterCommands();
        commands.Print();
        sjsu::Delay(2s);
        
        arguments = tri_wheel.SetLegArguments(ModeSelect::SelectMode(lerp.Lerp(mode_switch.SwitchSteerMode(commands, arguments))));
        arguments.Print();
        sjsu::Delay(2s);
    }

    return 0;
}