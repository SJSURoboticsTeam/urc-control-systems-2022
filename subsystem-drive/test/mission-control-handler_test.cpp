#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "implementations/mission-control-handler.hpp"
#include "dto/drive-dto.hpp"

namespace sjsu::drive
{
    TEST_CASE("Mission Control Handler")
    {
        MissionControlHandler mission_control_handler;
        SECTION("Should properly parse a default starting command from mission control")
        {
            drive_commands expected_commands;
            expected_commands.is_operational = 1;
            expected_commands.speed = 100;
            expected_commands.angle = 12;

            char mc_commands[200];
            snprintf(
                mc_commands, 200, kResponseBodyFormat,
                expected_commands.heartbeat_count, expected_commands.is_operational, expected_commands.wheel_orientation, expected_commands.mode, expected_commands.speed, expected_commands.angle);
            std::string mc_commands_string = mc_commands;

            drive_commands actual_commands = mission_control_handler.ParseMissionControlData(mc_commands_string);
            CHECK_EQ(expected_commands.mode, actual_commands.mode);
            CHECK_EQ(expected_commands.speed, actual_commands.speed);
            CHECK_EQ(expected_commands.angle, actual_commands.angle);
            CHECK_EQ(expected_commands.wheel_orientation, actual_commands.wheel_orientation);
            CHECK_EQ(expected_commands.is_operational, actual_commands.is_operational);
            CHECK_EQ(expected_commands.heartbeat_count, actual_commands.heartbeat_count);
        }
    }
}