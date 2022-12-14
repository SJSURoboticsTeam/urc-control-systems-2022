#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../dto/arm-dto.hpp"
#include "implementations/rules-engine.hpp"

namespace sjsu::arm
{
    TEST_CASE("Rules Engine Testing")
    {
        RulesEngine engine;
        mc_commands commands, response;

        SECTION("should validate max and min finger angles clamping")
        {
            commands.mode = 'H';
            commands.first_angle = 181;
            commands.second_angle = 190;
            commands.third_angle = -90;
            commands.fourth_angle = 200;
            commands.fifth_angle = -180;

            response = engine.ValidateCommands(commands);

            CHECK_NE(commands.first_angle, response.first_angle);
            CHECK_NE(commands.second_angle, response.second_angle);
            CHECK_NE(commands.third_angle, response.third_angle);
            CHECK_NE(commands.fourth_angle, response.fourth_angle);
            CHECK_NE(commands.fifth_angle, response.fifth_angle);
        }

        SECTION("should validate max and min joint angles clamping")
        {
            commands.mode = 'J';
            commands.second_angle = 100;
            commands.third_angle = -180;
            commands.fourth_angle = 120;

            response = engine.ValidateCommands(commands);

            CHECK_NE(commands.second_angle, response.second_angle);
            CHECK_NE(commands.third_angle, response.third_angle);
            CHECK_NE(commands.fourth_angle, response.fourth_angle);
        }

    }
}