#include "../implementations/steer-modes.hpp";

using namespace sjsu::drive;

int main()
{
    drive_commands commands;
    tri_wheel_router_arguments arguments;
    SteerModes steermode{};
    arguments = steermode.DriveSteering(commands);

    return 0;
}