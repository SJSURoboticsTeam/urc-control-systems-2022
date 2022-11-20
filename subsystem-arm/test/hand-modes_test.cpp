#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/arm-modes.hpp"
#include "../dto/arm-dto.hpp"
#include "../implementations/pca9685.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Mode Testing")
    {
        SECTION("should set hand angles based off mc commands")
        {
            mc_commands commands = {first_angle:1, second_angle:2, third_angle:3, fourth_angle:4, fifth_angle:5};
            arm_arguments args;
            args = ArmMode::HandMode(commands, args);
            CHECK(args.hand_args.pinky_angle == commands.first_angle);
            CHECK(args.hand_args.ring_angle == commands.second_angle);
            CHECK(args.hand_args.middle_angle == commands.third_angle);
            CHECK(args.hand_args.index_angle == commands.fourth_angle);
            CHECK(args.hand_args.thumb_angle == commands.fifth_angle);
        }
    }
}