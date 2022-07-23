#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../dto/arm-dto.hpp"
#include "implementations/hand/rules-engine.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Rules Engine")
    {
        HandRulesEngine engine;
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

        SECTION("should validate is_operational logic")
        {
            commands.is_operational = 0;
            commands.index_angle = 100;

            hand_arguments response = engine.ValidateCommands(commands);
            CHECK_NE(commands.index_angle, response.index_angle);
        }

        SECTION("should validate max and min finger angles clamping")
        {
            commands.is_operational = -1;
            commands.thumb_angle = -180;
            commands.index_angle = 200;
            commands.middle_angle = -90;
            commands.ring_angle = 190;
            commands.pinky_angle = 181;

            hand_arguments response = engine.ValidateCommands(commands);
            CHECK_NE(commands.thumb_angle, response.thumb_angle);
            CHECK_NE(commands.index_angle, response.index_angle);
            CHECK_NE(commands.middle_angle, response.middle_angle);
            CHECK_NE(commands.ring_angle, response.ring_angle);
            CHECK_NE(commands.pinky_angle, response.pinky_angle);
        }
    }
}