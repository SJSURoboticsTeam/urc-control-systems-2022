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

        SECTION("2.1 Should set angles to minimum angle when in close mode")
        {
            hand_arguments original_commands{30, 30, 30, 30, 30};
            hand_arguments args = HandModes::CloseMode(original_commands);
            CHECK_EQ(args.pinky_angle, original_commands.pinky_angle);
            CHECK_EQ(args.ring_angle, original_commands.ring_angle);
            CHECK_EQ(args.middle_angle, original_commands.middle_angle);
            CHECK_EQ(args.index_angle, original_commands.index_angle);
            CHECK_EQ(args.thumb_angle, original_commands.thumb_angle);
        }

        SECTION("3.1 Should set angles to correct angle give OpenMode mode angles")
        {
            hand_arguments original_commands{180, 180, 180, 180, 180};
            hand_arguments args = HandModes::OpenMode(original_commands);
            CHECK_EQ(args.pinky_angle, original_commands.pinky_angle);
            CHECK_EQ(args.ring_angle, original_commands.ring_angle);
            CHECK_EQ(args.middle_angle, original_commands.middle_angle);
            CHECK_EQ(args.index_angle, original_commands.index_angle);
            CHECK_EQ(args.thumb_angle, original_commands.thumb_angle);
        }

        SECTION("4.1 Hand Arguments should recieve correct angle from finger angle")
        {
            int finger_angle = 90;
            hand_arguments original_commands{finger_angle, finger_angle, finger_angle, finger_angle, finger_angle};
            hand_arguments args = HandModes::SimultaneousMode(original_commands);
            CHECK_EQ(args.pinky_angle, original_commands.finger_angle);
            CHECK_EQ(args.ring_angle, original_commands.finger_angle);
            CHECK_EQ(args.middle_angle, original_commands.finger_angle);
            CHECK_EQ(args.index_angle, original_commands.finger_angle);
            CHECK_EQ(args.thumb_angle, original_commands.finger_angle);
        }
        SECTION("4.2 Hand Arguments should recieve correct finger_angle from mission control"){
            
            hand_arguments original_commands{90};
            hand_arguments args = HandModes::SimultaneousMode(original_commands);
            CHECK_EQ(args.finger_angle, original_commands.finger_angle);

        }
    }
}