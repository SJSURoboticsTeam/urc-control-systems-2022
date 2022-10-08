#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/arm-modes.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Arm Mode Testing")
    {
        SECTION("should set angles to correct simultaneous mode angles")
        {
            joint_arguments original_commands = {10, 20, 30, 40, 50, 60, 70, 80};
            joint_arguments args = JointModes::SimultaneousMode(original_commands);
            CHECK(args.rotunda_angle == original_commands.rotunda_angle);
            CHECK(args.shoulder_angle == original_commands.shoulder_angle);
            CHECK(args.elbow_angle == original_commands.elbow_angle);
            CHECK(args.wrist_pitch_angle == original_commands.wrist_pitch_angle);
            CHECK(args.wrist_roll_angle == original_commands.wrist_roll_angle);
        }

        SECTION("should ignore arguments and set angles to proper condensed mode angles")
        {
            joint_arguments original_commands = {10, 10, 10, 10, 10, 10, 10, 10, 'S'};
            joint_arguments args = JointModes::CondensedMode(original_commands);
            CHECK_NE(args.rotunda_angle, original_commands.rotunda_angle);
            CHECK_NE(args.shoulder_angle, original_commands.shoulder_angle);
            CHECK_NE(args.elbow_angle, original_commands.elbow_angle);
            CHECK_NE(args.wrist_pitch_angle, original_commands.wrist_pitch_angle);
            CHECK_NE(args.wrist_roll_angle, original_commands.wrist_pitch_angle);
        }
    }
}