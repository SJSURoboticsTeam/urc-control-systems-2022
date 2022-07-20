#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/hand/hand-modes.hpp"
#include "../dto/arm-dto.hpp"
#include "../implementations/pca9685.hpp"


namespace sjsu::arm
{
    TEST_CASE("Hand Mode Testing")
    {
        SECTION("1.1 Should set angles to correct given individual mode angles")
        {
            hand_arguments original_commands{100, 100, 100, 100, 100};
            hand_arguments args = HandModes::IndividualMode(original_commands);
            CHECK_EQ(args.pinky_angle, original_commands.pinky_angle);
            CHECK_EQ(args.ring_angle, original_commands.ring_angle);
            CHECK_EQ(args.middle_angle, original_commands.middle_angle);
            CHECK_EQ(args.index_angle, original_commands.index_angle);
            CHECK_EQ(args.thumb_angle, original_commands.thumb_angle);
        }

        SECTION("1.2 Should set angles to minimum angle when in close mode")
        {
            hand_arguments original_commands{30, 30, 30, 30, 30};
            hand_arguments args = HandModes::CloseMode(original_commands);
            CHECK_EQ(args.pinky_angle, original_commands.pinky_angle);
            CHECK_EQ(args.ring_angle, original_commands.ring_ange);
            CHECK_EQ(args.middle_angle, original_commands.middle_angle);
            CHECK_EQ(args.index_angle, original_commands.index_angle);
            CHECK_EQ(args.thumb_angle, original_commands.thumb_angle);
        }

        SECTION("1.3 Should set angles to correct angle gievn OpenMode mode angles")
        {
            hand_arguments original_commands{180, 180, 180, 180, 180};
            hand_arguments args = HandModes::OpenMode(original_commands);
            CHECK(args.pinky_angle == original_commands.max_angle);
            CHECK(args.ring_angle == original_commands.max_angle);
            CHECK(args.middle_angle == original_commands.max_angle);
            CHECK(args.index_angle == original_commands.max_angle);
            CHECK(args.thumb_angle == original_commands.max_angle);
        }

        SECTION("1.4 Should set angles to correct angle given simultaneous mode angles")
        {
            int finger_angle = 90;
            hand_arguments original_commands{finger_angle, finger_angle, finger_angle, finger_angle, finger_angle};
            hand_arguments args = HandModes::SimultaneousMode(original_commands);
            CHECK(args.pinky_angle == original_commands.finger_angle);
            CHECK(args.ring_angle == original_commands.finger_angle);
            CHECK(args.middle_angle == original_commands.finger_angle);
            CHECK(args.index_angle == original_commands.finger_angle);
            CHECK(args.thumb_angle == original_commands.finger_angle);
        }
    }
}