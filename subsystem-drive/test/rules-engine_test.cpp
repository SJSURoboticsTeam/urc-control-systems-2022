#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/rules-engine.hpp"
#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    TEST_CASE("Testing Mode Switcher...")
    {
        SECTION("1.1: If heartbeat is synced, rover is operational, and speed is less then 100, speed shouldn't change")
        {
            RulesEngine rules_engine;
            drive_commands commands{'D', 80, 10, 0, 1, 0};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, 80);
            commands.heartbeat_count = 1;
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, 80);
        }
        SECTION("1.2: If heartbeat is not synced then speed should drop to 0, then it should proceed as normal if it resyncs")
        {
            RulesEngine rules_engine;
            drive_commands commands{'D', 80, 10, 0, 1, 10};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, 0);
            commands = {'D', 80, 10, 0, 1, 0};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, 80);
        }
        SECTION("1.3: If the rover is not operational then speed should drop to 0 then speed back up if it is operational")
        {
            RulesEngine rules_engine;
            drive_commands commands{'D', 80, 10, 0, 0, 0};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, 0);
            commands = {'D', 80, 10, 0, 1, 1};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, 80);
        }
        SECTION("1.4: If the speed is greater than 100 then clamp it to 100, if speed is less then -100, clamp it to -100")
        {
            RulesEngine rules_engine;
            drive_commands commands{'D', RulesEngine::kMaxSpeed, 10, 0, 1, 0};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, RulesEngine::kMaxSpeed);
            commands = {'D', 101, 10, 0, 1, 1};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, RulesEngine::kMaxSpeed);
            commands = {'D', -RulesEngine::kMaxSpeed, 10, 0, 1, 2};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, -RulesEngine::kMaxSpeed);
            commands = {'D', -101, 10, 0, 1, 3};
            commands = rules_engine.ValidateCommands(commands);
            CHECK_EQ(commands.speed, -RulesEngine::kMaxSpeed);
        }
    }
}