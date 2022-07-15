#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/hand/hand-modes.hpp"
#include "../dto/arm-dto.hpp"
#include "../implementations/pca9685.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Mode Testing")
    {
        SECTION("Should set angles to correct given manual mode angles")
        {
            hand_arguments original_commands{100, 100, 100, 100, 100, 100, 100, 100};
            hand_arguments args = HandModes::ManualMode(original_commands);
            CHECK(args.pinky_angle == original_commands.pinky_angle);
            CHECK(args.ring_angle == original_commands.ring_angle);
            CHECK(args.middle_angle == original_commands.middle_angle);
            CHECK(args.index_angle == original_commands.index_angle);
            CHECK(args.thumb_angle == original_commands.thumb_angle);
        }
    }
}