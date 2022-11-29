#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/arm-modes.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Arm Mode Testing")
    {
        SECTION("should set joint angles based off mc commands")
        {
            mc_commands commands = {first_angle:1, second_angle:2, third_angle:3, fourth_angle:4, fifth_angle:5};
            arm_arguments args;
            args = ArmMode::JointMode(commands, args);
            CHECK(args.joint_args.rotunda_angle == commands.first_angle);
            CHECK(args.joint_args.shoulder_angle == commands.second_angle);
            CHECK(args.joint_args.elbow_angle == commands.third_angle);
            CHECK(args.joint_args.wrist_pitch_angle == commands.fourth_angle);
            CHECK(args.joint_args.wrist_roll_angle == commands.fifth_angle);
        }
    }
}