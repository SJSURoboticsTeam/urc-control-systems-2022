#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/mode-switcher.hpp"
#include "../dto/motor-feedback-dto.hpp"

namespace sjsu::drive
{

    TEST_CASE("Testing Mode Switcher...")
    {
        SECTION("1.1: shouldn't change anything when drive mode is left alone and first turned on.")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            motor_feedback feedback;
            ModeSwitch switcher;
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
            CHECK_EQ(commands.speed, 0);
        }
        SECTION("1.2: when speed is not zero the mode should not switch until speed is 0.")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            motor_feedback feedback;
            ModeSwitch switcher;
            arguments.back.hub.speed = 10;
            commands.mode = 'T';
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
            CHECK_EQ(commands.speed, 0);
            arguments.back.hub.speed = 0;
            arguments.right.hub.speed = 10;
            commands.mode = 'T';
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
            CHECK_EQ(commands.speed, 0);
            arguments.right.hub.speed = 0;
            arguments.left.hub.speed = 10;
            commands.mode = 'T';
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
            CHECK_EQ(commands.speed, 0);
            arguments.left.hub.speed = 0;
            commands.mode = 'T';
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            CHECK_EQ(commands.mode, 'T');
            CHECK_EQ(commands.angle, 0);
            CHECK_EQ(commands.speed, 0);
        }
        SECTION("1.3: if hub speed is 0 and steer speed is also 0 then mode should switch and after 2 calls, the speed should be able to be set.")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            motor_feedback feedback;
            ModeSwitch switcher;
            arguments.back.steer.speed = 0;
            arguments.right.steer.speed = 0;
            arguments.left.steer.speed = 0;
            feedback.back_steer_speed = 0_rpm;
            feedback.left_steer_speed = 0_rpm;
            feedback.right_steer_speed = 0_rpm;
            commands.mode = 'T';
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            CHECK_EQ(commands.mode, 'T');
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            commands.speed = 30;
            commands = switcher.SwitchSteerMode(commands, arguments, feedback);
            CHECK_EQ(commands.speed, 30);
        }
    }
}