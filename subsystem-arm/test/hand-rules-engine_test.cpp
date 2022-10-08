#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../dto/arm-dto.hpp"
#include "implementations/rules-engine.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Rules Engine")
    {
        RulesEngine engine;
        hand_arguments commands;
        // TODO: FIX THESE TESTS
        // SECTION("should validate not change hand state")
        // {
        //     commands.middle_angle = 90;
        //     commands.index_angle = 90;

        //     hand_arguments response = engine.ValidateCommands(commands);
        //     CHECK_EQ(response.index_angle, commands.index_angle);
        //     commands.middle_angle = 20;
        //     commands.index_angle = 30;
        //     response = engine.ValidateCommands(commands);
        //     CHECK_NE(commands.middle_angle, response.middle_angle);
        //     CHECK_NE(commands.index_angle, response.index_angle);
        // }

        // SECTION("should validate max and min finger angles clamping")
        // {
        //     commands.thumb_angle = -180;
        //     commands.index_angle = 200;
        //     commands.middle_angle = -90;
        //     commands.ring_angle = 190;
        //     commands.pinky_angle = 181;

        //     hand_arguments response = engine.ValidateCommands(commands);
        //     CHECK_NE(commands.thumb_angle, response.thumb_angle);
        //     CHECK_NE(commands.index_angle, response.index_angle);
        //     CHECK_NE(commands.middle_angle, response.middle_angle);
        //     CHECK_NE(commands.ring_angle, response.ring_angle);
        //     CHECK_NE(commands.pinky_angle, response.pinky_angle);
        // }
    }
}