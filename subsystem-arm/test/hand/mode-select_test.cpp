#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/hand/mode-select.hpp"
#include "../dto/arm-dto.hpp"
#include "../implementations/pca9685.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Mode Select Testing")
    {
        // Stay in the default mode be rover powers on -- Ahmed
        // Change to the correct mode it's given from mission control -- Michael
        // Mode should not change while fingers are still in motion -- TK
        SECTION("1.1 Change to the correct mode it's given from mission control")
        {
            hand_arguments original_command_I; 
            hand_arguments original_command_C;
            original_command_C.mode = 'C';
            hand_arguments original_command_O;
            original_command_O.mode = 'O';
            hand_arguments original_command_S;
            original_command_S.mode = 'S';

            hand_arguments args_I = ModeSelect::SelectMode(original_command_I);
            CHECK_EQ(args_I.mode, original_command_I.mode);

            hand_arguments args_C = ModeSelect::SelectMode(original_command_C);
            CHECK_EQ(args_C.mode, original_command_C.mode);

            hand_arguments args_O = ModeSelect::SelectMode(original_command_O);
            CHECK_EQ(args_O.mode, original_command_O.mode);

            hand_arguments args_S = ModeSelect::SelectMode(original_command_S);
            CHECK_EQ(args_S.mode, original_command_S.mode);
        }
        SECTION("2.1: Should stay in default mode and default angle when rover powers on")
        {
            hand_arguments default_;
            CHECK_EQ(default_.mode, 'I');
            int default_angle = 0;
            CHECK_EQ(default_.pinky_angle, default_angle);
            CHECK_EQ(default_.ring_angle, default_angle);
            CHECK_EQ(default_.middle_angle, default_angle);
            CHECK_EQ(default_.index_angle, default_angle);
            CHECK_EQ(default_.thumb_angle, default_angle);
        }
    }
}