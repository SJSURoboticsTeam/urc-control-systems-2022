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
            commands.angle = -25;
            commands.speed = 20;
            arguments = SteerModes::DriveSteering(commands);
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
            arguments = SteerModes::DriveSteering(commands);
            CHECK_EQ(arguments.back.hub.angle, 0);
            CHECK_EQ(arguments.back.hub.speed, 0);
            CHECK_EQ(arguments.back.steer.angle, SteerModes::kBackLegDriveOffset);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.left.hub.angle, 0);
            CHECK_EQ(arguments.left.hub.speed, 0);
            CHECK_EQ(arguments.left.steer.angle, SteerModes::kLeftLegDriveOffset);
            CHECK_EQ(arguments.left.steer.speed, 5);
            CHECK_EQ(arguments.right.hub.angle, 0);
            CHECK_EQ(arguments.right.hub.speed, 0);
            CHECK_EQ(arguments.right.steer.angle, SteerModes::kRightLegDriveOffset);
            CHECK_EQ(arguments.right.steer.speed, 5);
        }
        SECTION("1.2: Should give correct sign when drive mode is given a negative angle.")
        {
            drive_commands commands{};
            float angle = -25;
            commands.angle = angle;
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::DriveSteering(commands);
            CHECK_EQ(arguments.back.hub.angle, 0);
            CHECK_EQ(arguments.back.hub.speed, 0);
            CHECK_GT(arguments.back.steer.angle, 0);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.left.hub.angle, 0);
            CHECK_EQ(arguments.left.hub.speed, 0);
            CHECK_EQ(arguments.left.steer.angle - 360, doctest::Approx(-angle).epsilon(1.0));
            CHECK_EQ(arguments.left.steer.speed, 5);
            CHECK_EQ(arguments.right.hub.angle, 0);
            CHECK_EQ(arguments.right.hub.speed, 0);
            CHECK_GT(arguments.right.steer.angle, 0);
            CHECK_EQ(arguments.right.steer.speed, 5);
        }
        SECTION("1.3: Should give correct sign when drive mode is given a positive angle.")
        {
            drive_commands commands{};
            float angle = 25;
            commands.angle = angle;
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::DriveSteering(commands);
            CHECK_EQ(arguments.back.hub.angle, 0);
            CHECK_EQ(arguments.back.hub.speed, 0);
            CHECK_GT(arguments.back.steer.angle, 0);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.left.hub.angle, 0);
            CHECK_EQ(arguments.left.hub.speed, 0);
            CHECK_GT(arguments.left.steer.angle, 0);
            CHECK_EQ(arguments.left.steer.speed, 5);
            CHECK_EQ(arguments.right.hub.angle, 0);
            CHECK_EQ(arguments.right.hub.speed, 0);
            CHECK_LT(arguments.right.steer.angle, arguments.left.steer.angle);
            CHECK_EQ(arguments.right.steer.speed, 5);
        }
        SECTION("1.4: Speed on each wheel should be the same when angle is 0 (default).")
        {
            drive_commands commands{};
            float speed = 90;
            commands.speed = speed;
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::DriveSteering(commands);
            CHECK_EQ(arguments.back.hub.speed, speed);
            CHECK_EQ(arguments.left.hub.speed, -speed);
            CHECK_EQ(arguments.right.hub.speed, -speed);
            commands.speed = -speed;
            arguments = SteerModes::DriveSteering(commands);
            CHECK_EQ(arguments.back.hub.speed, -speed);
            CHECK_EQ(arguments.left.hub.speed, speed);
            CHECK_EQ(arguments.right.hub.speed, speed);
        }
        SECTION("1.5: inner wheel should be going the slowest, outer wheel the fastest, and back wheel in between.")
        {
            drive_commands commands{};
            float speed = 90;
            commands.speed = speed;
            float angle = 25;
            commands.angle = angle;
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::DriveSteering(commands);
            CHECK_GT(arguments.back.hub.speed, arguments.right.hub.speed);
            CHECK_LT(arguments.left.hub.speed, arguments.back.hub.speed);
            CHECK_EQ(arguments.right.hub.speed, -speed);
            commands.angle = -angle;
            arguments = SteerModes::DriveSteering(commands);
            CHECK_GT(arguments.back.hub.speed, arguments.left.hub.speed);
            CHECK_EQ(arguments.left.hub.speed, -speed);
            CHECK_GT(abs(arguments.right.hub.speed), abs(arguments.back.hub.speed));
        }
        SECTION("2.1: With default values, spin mode should have preset angles that don't change and speed should be 0.")
        {

            drive_commands commands{};
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::SpinSteering(commands);
            CHECK_EQ(arguments.back.steer.angle, SteerModes::kBackLegSpinOffset);
            CHECK_EQ(arguments.left.steer.angle, SteerModes::kLeftLegSpinOffset);
            CHECK_EQ(arguments.right.steer.angle, SteerModes::kRightLegSpinOffset);
            CHECK_EQ(arguments.back.hub.speed, 0);
            CHECK_EQ(arguments.left.hub.speed, 0);
            CHECK_EQ(arguments.right.hub.speed, 0);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.right.steer.speed, 5);
            CHECK_EQ(arguments.left.steer.speed, 5);
        }
        SECTION("2.2: With any angle, no values should change.")
        {
            drive_commands commands{};
            commands.angle = 90;
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::SpinSteering(commands);
            CHECK_EQ(arguments.back.steer.angle, SteerModes::kBackLegSpinOffset);
            CHECK_EQ(arguments.left.steer.angle, SteerModes::kLeftLegSpinOffset);
            CHECK_EQ(arguments.right.steer.angle, SteerModes::kRightLegSpinOffset);
            CHECK_EQ(arguments.back.hub.speed, 0);
            CHECK_EQ(arguments.left.hub.speed, 0);
            CHECK_EQ(arguments.right.hub.speed, 0);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.right.steer.speed, 5);
            CHECK_EQ(arguments.left.steer.speed, 5);
            commands.angle = -90;
            arguments = SteerModes::SpinSteering(commands);
            CHECK_EQ(arguments.back.steer.angle, SteerModes::kBackLegSpinOffset);
            CHECK_EQ(arguments.left.steer.angle, SteerModes::kLeftLegSpinOffset);
            CHECK_EQ(arguments.right.steer.angle, SteerModes::kRightLegSpinOffset);
            CHECK_EQ(arguments.back.hub.speed, 0);
            CHECK_EQ(arguments.left.hub.speed, 0);
            CHECK_EQ(arguments.right.hub.speed, 0);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.right.steer.speed, 5);
            CHECK_EQ(arguments.left.steer.speed, 5);
        }
        SECTION("2.3: When given a positive speed the argument speeds should be positive.")
        {
            drive_commands commands{};
            float speed = 90;
            commands.speed = speed;
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::SpinSteering(commands);
            CHECK_EQ(arguments.back.steer.angle, SteerModes::kBackLegSpinOffset);
            CHECK_EQ(arguments.left.steer.angle, SteerModes::kLeftLegSpinOffset);
            CHECK_EQ(arguments.right.steer.angle, 0);
            CHECK_EQ(arguments.back.hub.speed, speed);
            CHECK_EQ(arguments.left.hub.speed, -speed);
            CHECK_EQ(arguments.right.hub.speed, speed);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.right.steer.speed, 5);
            CHECK_EQ(arguments.left.steer.speed, 5);
        }
        SECTION("2.4: When given a negative speed the argument speeds should be negative.")
        {
            drive_commands commands{};
            float speed = -90;
            commands.speed = speed;
            tri_wheel_router_arguments arguments;
            arguments = SteerModes::SpinSteering(commands);
            CHECK_EQ(arguments.back.steer.angle, SteerModes::kBackLegSpinOffset);
            CHECK_EQ(arguments.left.steer.angle, SteerModes::kLeftLegSpinOffset);
            CHECK_EQ(arguments.right.steer.angle, SteerModes::kRightLegSpinOffset);
            CHECK_EQ(arguments.back.hub.speed, speed);
            CHECK_EQ(arguments.left.hub.speed, -speed);
            CHECK_EQ(arguments.right.hub.speed, speed);
            CHECK_EQ(arguments.back.steer.speed, 5);
            CHECK_EQ(arguments.right.steer.speed, 5);
            CHECK_EQ(arguments.left.steer.speed, 5);
        }
        SECTION("2.5: if one wheel is turning all wheels should be turning")
        {
             tri_wheel_router_arguments arguments;
             if(arguments.back.steer.angle!=0){
                   CHECK(arguments.left.steer.angle!=0);
                   CHECK(arguments.right.steer.angle!=0);

             }else if(arguments.left.steer.angle!=0){
                CHECK(arguments.back.steer.angle!=0);
                CHECK(arguments.right.steer.angle!=0);
             }else if(arguments.right.steer.angle!=0){
                    CHECK(arguments.back.steer.angle!=0);
                CHECK(arguments.left.steer.angle!=0);
             }
            
        }
        
    }
}