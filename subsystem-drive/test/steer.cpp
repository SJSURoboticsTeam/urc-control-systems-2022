#include "testing/testing_frameworks.hpp"
#include "../implementations/steer-modes.hpp"
#include "utility/log.hpp"

namespace sjsu::drive
{

    TEST_CASE("Drive system testing")
    {
        drive_commands commands;
        tri_wheel_router_arguments arguments;

        SECTION("1.1 should start with default values")
        {
            SteerModes steermode{};
            commands.angle = 20;
            commands.speed = 25;
            arguments = steermode.DriveSteering(commands);
            // CHECK(arguments.left.steer.angle, 100);
            // printf(to_string(arguments.left.steer.angle));
            // printf(arguments.left.steer.speed);
            // printf(arguments.left.hub.angle);
            // printf(arguments.left.hub.speed);

            // printf(arguments.right.steer.angle);
            // printf(arguments.right.steer.speed);
            // printf(arguments.right.hub.angle);
            // printf(arguments.right.hub.speed);

            // printf(arguments.back.steer.angle);
            // printf(arguments.back.steer.speed);
            // printf(arguments.back.hub.angle);
            // printf(arguments.back.hub.speed);
        }
    }
}