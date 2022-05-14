#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/mode-switcher.hpp"

namespace sjsu::drive
{

    TEST_CASE("Testing Mode Switcher...")
    {
        SECTION("1.1: shouldn't change anything when drive mode is left alone...")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            ModeSwitch switcher;
            commands = switcher.SwitchSteerMode(commands, arguments);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
            CHECK_EQ(commands.speed, 0);
        }
        SECTION("1.2: shouldn't change drive mode when speed is not 0...")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            ModeSwitch switcher;
            commands.mode = 'T';
            arguments.back.hub.speed = 10;
            commands = switcher.SwitchSteerMode(commands, arguments);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
            arguments.back.hub.speed = 0;
            arguments.left.hub.speed = 10;
            commands = switcher.SwitchSteerMode(commands, arguments);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
            arguments.left.hub.speed = 0;
            arguments.right.hub.speed = 10;
            commands = switcher.SwitchSteerMode(commands, arguments);
            CHECK_EQ(commands.mode, 'D');
            CHECK_EQ(commands.angle, 0);
        }
        SECTION("1.3: should change drive mode when speed is 0...")
        {
            drive_commands commands;
            tri_wheel_router_arguments arguments;
            ModeSwitch switcher;
            commands.mode = 'T';
            commands = switcher.SwitchSteerMode(commands, arguments);
            CHECK_EQ(commands.mode, 'T');
        }
        
    }
}