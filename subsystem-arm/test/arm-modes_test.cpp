#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "implementations/arm-modes.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Arm Mode Testing")
    {
        SECTION("should set angles to correct simulataneous mode angles")
        {
            arm_commands original_commands {100, 100, 100, 100, 100};
            arm_arguments args = ArmModes::SimulataneousMode(original_commands);
            CHECK(args.rotunda_angle == original_commands.rotunda_angle);
            CHECK(args.shoulder_angle == original_commands.shoulder_angle);
            CHECK(args.elbow_angle == original_commands.elbow_angle);
            CHECK(args.wrist_pitch_angle == original_commands.wrist_pitch_angle);
            CHECK(args.wrist_yaw_angle == original_commands.wrist_pitch_angle);
        }

        SECTION("should ignore arguments and set angles to proper condensed mode angles")
        {
            arm_commands original_commands {100, 100, 100, 100, 100};
            arm_arguments args = ArmModes::CondensedMode(original_commands);
            CHECK(args.rotunda_angle != original_commands.rotunda_angle);
            CHECK(args.shoulder_angle != original_commands.shoulder_angle);
            CHECK(args.elbow_angle != original_commands.elbow_angle);
            CHECK(args.wrist_pitch_angle != original_commands.wrist_pitch_angle);
            CHECK(args.wrist_yaw_angle != original_commands.wrist_pitch_angle);
        }
    }
}