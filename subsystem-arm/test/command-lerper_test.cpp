#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "implementations/command-lerper.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Command Lerper Testing")
    {
        CommandLerper lerp;
        SECTION("should lerp all angles by certain ammount")
        {
            arm_commands original_commands {100, 100, 100, 100, 100};
            arm_commands lerped_commands = lerp.Lerp(original_commands);
            CHECK(lerped_commands.rotunda_angle != original_commands.rotunda_angle);
            CHECK(lerped_commands.shoulder_angle != original_commands.shoulder_angle);
            CHECK(lerped_commands.elbow_angle != original_commands.elbow_angle);
            CHECK(lerped_commands.wrist_pitch_angle != original_commands.wrist_pitch_angle);
            CHECK(lerped_commands.wrist_yaw_angle != original_commands.wrist_yaw_angle);
        }
    }
}