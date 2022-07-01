#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/joints/joint-modes.hpp"
#include "../dto/hand-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Mode Testing")
    {
        SECTION("Should set angles to correct given manual mode angles")
        {
            hand_arguments original_commands {100, 100, 100, 100, 100, 100, 100, 100};
            hand_arguments args = HandModes::ManualMode(original_commands);
            CHECK(args.hand_args.pinky_angle == original_commands.hand_args.pinky_angle);
            CHECK(args.hand_args.ring_angle == original_commands.hand_args.ring_angle);            
            CHECK(args.hand_args.middle_angle == original_commands.hand_args.middle_angle);
            CHECK(args.hand_args.index_angle == original_commands.hand_args.index_angle);
            CHECK(args.hand_args.thumb_angle == original_commands.hand_args.thumb_angle);
        }


    }
}