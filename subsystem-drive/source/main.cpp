#include "utility/log.hpp"

#include "../implementations/steer-modes.hpp"

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
    SteerModes steermode;
    while (1)
    {
        commands = SerialEnterCommands();
        commands.Print();
        sjsu::Delay(2s);

        tri_wheel_router_arguments arguments = steermode.DriveSteering(commands);
        arguments.Print();
        sjsu::Delay(2s);
    }

    return 0;
}