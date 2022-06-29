#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../dto/arm-dto.hpp"
#include "implementations/hand/rules-engine.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Rules Engine")
    {
        RulesEngine engine;
        hand_arguments commands;
        SECTION("should validate heartbeat logic")
        {
            commands.is_operational = 1;
            hand_arguments response = engine.ValidateCommands(commands);
            CHECK_EQ(response.heartbeat_count, commands.heartbeat_count);
            commands.heartbeat_count = 1;
            response = engine.ValidateCommands(commands);
            CHECK_EQ(response.heartbeat_count, commands.heartbeat_count);
        }

        SECTION("should validate not change hand state")
        {
            commands.is_operational = 1;
            commands.middle_angle = 10;
            commands.index_angle = 10;

            hand_arguments response = engine.ValidateCommands(commands);
            CHECK_EQ(response.index_angle, commands.index_angle);
            commands.middle_angle = 20;
            commands.index_angle = 30;
            response = engine.ValidateCommands(commands);
            CHECK_NE(commands.middle_angle, response.middle_angle);
            CHECK_NE(commands.index_angle, response.index_angle);
        }
    }
}