#include "testing/testing_frameworks.hpp"
#include "../implementations/steer-modes.hpp"
#include "utility/log.hpp"

namespace sjsu::drive
{

    TEST_CASE("Drive system testing")
    {
        SECTION("Just printing out some values")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            SteerModes steermode;
            commands.angle = -25;
            commands.speed = 20;
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
        SECTION("1.1: All values should be 0 or 5 with no changes post calculations for drive mode.")
        {
            drive_commands commands{};
            tri_wheel_router_arguments arguments;
            SteerModes steermode;
            arguments = steermode.DriveSteering(commands);
            CHECK_EQ(arguments.back.hub.angle, 0);
            CHECK_EQ(arguments.back.hub.speed, 0);
            CHECK_EQ(arguments.back.steer.angle, 0);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.left.hub.angle, 0);
            CHECK_EQ(arguments.left.hub.speed, 0);
            CHECK_EQ(arguments.left.steer.angle, 0);
            CHECK_EQ(arguments.left.steer.speed, 5);
            CHECK_EQ(arguments.right.hub.angle, 0);
            CHECK_EQ(arguments.right.hub.speed, 0);
            CHECK_EQ(arguments.right.steer.angle, 0);
            CHECK_EQ(arguments.right.steer.speed, 5);
        }
        SECTION("1.2: Should give correct sign when drive mode is given a negative angle.")
        {
            drive_commands commands{};
            commands.angle = -25;
            tri_wheel_router_arguments arguments;
            SteerModes steermode;
            arguments = steermode.DriveSteering(commands);
            CHECK(arguments.back.hub.angle == 0);
            CHECK(arguments.back.hub.speed == 0);
            CHECK(arguments.back.steer.angle < 0);
            CHECK(arguments.back.steer.speed == 5);
            CHECK(arguments.left.hub.angle == 0);
            CHECK(arguments.left.hub.speed == 0);
            CHECK(arguments.left.steer.angle == -25);
            CHECK(arguments.left.steer.speed == 5);
            CHECK(arguments.right.hub.angle == 0);
            CHECK(arguments.right.hub.speed == 0);
            CHECK(arguments.right.steer.angle < 0);
            CHECK(arguments.right.steer.speed == 5);
        }
        SECTION("1.3: Should give correct sign when drive mode is given a positive angle.")
        {
            drive_commands commands{};
            commands.angle = 25;
            tri_wheel_router_arguments arguments;
            SteerModes steermode;
            arguments = steermode.DriveSteering(commands);
            CHECK(arguments.back.hub.angle == 0);
            CHECK(arguments.back.hub.speed == 0);
            CHECK(arguments.back.steer.angle < 0);
            CHECK(arguments.back.steer.speed == 5);
            CHECK(arguments.left.hub.angle == 0);
            CHECK(arguments.left.hub.speed == 0);
            CHECK(arguments.left.steer.angle > 0);
            CHECK(arguments.left.steer.speed == 5);
            CHECK(arguments.right.hub.angle == 0);
            CHECK(arguments.right.hub.speed == 0);
            CHECK(arguments.right.steer.angle == 25);
            CHECK(arguments.right.steer.speed == 5);
        }
        SECTION("1.3: Speed on each wheel should be the same when angle is 0 (default).")
        {
            drive_commands commands{};
            commands.speed = 90;
            tri_wheel_router_arguments arguments;
            SteerModes steermode;
            arguments = steermode.DriveSteering(commands);
            CHECK(arguments.back.hub.speed == 90);
            CHECK(arguments.left.hub.speed == -90);
            CHECK(arguments.right.hub.speed == -90);
            commands.speed = -90;
            arguments = steermode.DriveSteering(commands);
            CHECK(arguments.back.hub.speed == -90);
            CHECK(arguments.left.hub.speed == 90);
            CHECK(arguments.right.hub.speed == 90);
        }
        SECTION("1.4: inner wheel should be going the slowest, outter wheel the fastest, and back wheel in between.")
        {
            drive_commands commands{};
            commands.speed = 90;
            commands.angle = 25;
            tri_wheel_router_arguments arguments;
            SteerModes steermode;
            arguments = steermode.DriveSteering(commands);
            CHECK(arguments.back.hub.speed > arguments.right.hub.speed);
            CHECK(-arguments.left.hub.speed > arguments.back.hub.speed);
            CHECK(arguments.right.hub.speed == -90);
            commands.angle = -25;
            arguments = steermode.DriveSteering(commands);
            CHECK(arguments.back.hub.speed > arguments.left.hub.speed);
            CHECK(arguments.left.hub.speed == -90);
            CHECK(-arguments.right.hub.speed > arguments.back.hub.speed);
        }
    }
}