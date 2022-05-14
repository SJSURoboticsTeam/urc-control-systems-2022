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
    CommandLerper lerp;
    bool stopped = false;
    while (1)
    {
        commands = SerialEnterCommands();
        commands.Print();
        sjsu::Delay(2s);

        if(arguments.back.hub.speed == 0 && arguments.right.hub.speed == 0 && arguments.left.hub.speed == 0) stopped = true;
        else stopped = false;
        
        arguments = tri_wheel.SetLegArguments(ModeSelect::SelectMode(lerp.Lerp(ModeSwitch::SwitchSteerMode(commands, stopped))));
        arguments.Print();
        sjsu::Delay(2s);
    }

    return 0;
}