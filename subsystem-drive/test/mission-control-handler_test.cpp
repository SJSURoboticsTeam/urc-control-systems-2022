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
            std::string mission_control_commands =
                "{\"heartbeat_count\":0,\"is_operational\":1,\"wheel_orientation\":0,\"drive_mode\":\"D\",\"speed\":0,\"angle\":0}";
            drive_commands actual_commands = mission_control_handler.ParseMissionControlData(mission_control_commands);
            CHECK_EQ(expected_commands.mode, actual_commands.mode);
            CHECK_EQ(expected_commands.speed, actual_commands.speed);
            CHECK_EQ(expected_commands.angle, actual_commands.angle);
            CHECK_EQ(expected_commands.wheel_orientation, actual_commands.wheel_orientation);
            CHECK_EQ(expected_commands.is_operational, actual_commands.is_operational);
            CHECK_EQ(expected_commands.heartbeat_count, actual_commands.heartbeat_count);
        }
    }
}