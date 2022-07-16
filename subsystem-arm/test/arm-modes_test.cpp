#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/joints/joint-modes.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Arm Mode Testing")
    {
        SECTION("should set angles to correct simulataneous mode angles")
        {
            arm_arguments original_commands {75, 75, 75, 75, 75, 75, 75, 75};
            arm_arguments args = JointModes::SimulataneousMode(original_commands);
            CHECK(args.joint_args.rotunda_angle == original_commands.joint_args.rotunda_angle);
            CHECK(args.joint_args.shoulder_angle == original_commands.joint_args.shoulder_angle);
            CHECK(args.joint_args.elbow_angle == original_commands.joint_args.elbow_angle);
            CHECK(args.joint_args.wrist_pitch_angle == original_commands.joint_args.wrist_pitch_angle);
            CHECK(args.joint_args.wrist_yaw_angle == original_commands.joint_args.wrist_pitch_angle);
        }

        SECTION("should ignore arguments and set angles to proper condensed mode angles")
        {
            arm_arguments original_commands {100, 100, 100, 100, 100, 100, 100, 100};
            arm_arguments args = JointModes::CondensedMode(original_commands);
            CHECK(args.joint_args.rotunda_angle != original_commands.joint_args.rotunda_angle);
            CHECK(args.joint_args.shoulder_angle != original_commands.joint_args.shoulder_angle);
            CHECK(args.joint_args.elbow_angle != original_commands.joint_args.elbow_angle);
            CHECK(args.joint_args.wrist_pitch_angle != original_commands.joint_args.wrist_pitch_angle);
            CHECK(args.joint_args.wrist_yaw_angle != original_commands.joint_args.wrist_pitch_angle);
        }
    }
}