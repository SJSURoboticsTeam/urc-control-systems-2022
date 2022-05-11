#include "testing/testing_frameworks.hpp"
#include "../implementations/steer-modes.hpp"
#include "utility/log.hpp"

namespace sjsu::drive
{

    TEST_CASE("Drive system testing")
    {
        SECTION("1.1 should start with default values")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            SteerModes steermode;
            commands.angle = 0;
            commands.speed = 0;
            arguments = steermode.DriveSteering(commands);
            printf("left steer: %f\n", arguments.left.steer.angle);
            printf("left steer: %f\n", arguments.left.steer.speed);
            printf("left hub: %f\n", arguments.left.hub.angle);
            printf("left hub: %f\n", arguments.left.hub.speed);

            printf("right steer: %f\n", arguments.right.steer.angle);
            printf("right steer: %f\n", arguments.right.steer.speed);
            printf("right hub: %f\n", arguments.right.hub.angle);
            printf("right hub: %f\n", arguments.right.hub.speed);

            printf("back steer: %f\n", arguments.back.steer.angle);
            printf("back steer: %f\n", arguments.back.steer.speed);
            printf("back hub: %f\n", arguments.back.hub.angle);
            printf("back hub: %f\n", arguments.back.hub.speed);
        }
    }
}