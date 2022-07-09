#include "utility/log.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "devices/actuators/servo/rmd_x.hpp"
#include "../common/esp.hpp"

#include "../implementations/mission-control-handler.hpp"
#include "../implementations/steer-modes.hpp"
#include "../implementations/tri-wheel-router.hpp"
#include "../implementations/mode-switcher.hpp"
#include "../implementations/mode-select.hpp"
#include "../implementations/command-lerper.hpp"
#include "../implementations/rules-engine.hpp"
#include "../dto/motor-feedback-dto.hpp"

using namespace sjsu::drive;

drive_commands SerialEnterCommands()
{
    drive_commands commands;
    sjsu::LogInfo("Enter in commands");
    scanf("%d,%d,%c", &commands.speed, &commands.angle, &commands.mode);
    return commands;
}

int main()
{
    sjsu::common::Esp esp;
    sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
    sjsu::StaticMemoryResource<1024> memory_resource;
    sjsu::CanNetwork can_network(can, &memory_resource);

    // RMD addresses 0x141 - 0x148 are available
    sjsu::RmdX left_steer_motor(can_network, 0x141);
    sjsu::RmdX left_hub_motor(can_network, 0x142);
    sjsu::RmdX right_steer_motor(can_network, 0x143);
    sjsu::RmdX right_hub_motor(can_network, 0x144);
    sjsu::RmdX back_steer_motor(can_network, 0x145);
    sjsu::RmdX back_hub_motor(can_network, 0x146);

    left_steer_motor.settings.gear_ratio = 6;
    left_hub_motor.settings.gear_ratio = 15;
    right_steer_motor.settings.gear_ratio = 6;
    right_hub_motor.settings.gear_ratio = 15;
    back_steer_motor.settings.gear_ratio = 6;
    back_hub_motor.settings.gear_ratio = 15;

    TriWheelRouter::leg right(right_steer_motor, right_hub_motor);
    TriWheelRouter::leg left(left_steer_motor, left_hub_motor);
    TriWheelRouter::leg back(back_steer_motor, back_hub_motor);

    TriWheelRouter tri_wheel{right, left, back};

    MissionControlHandler mission_control;
    drive_commands commands;
    motor_feedback motor_speeds;
    tri_wheel_router_arguments arguments;

    RulesEngine rules_engine;
    ModeSwitch mode_switch;
    CommandLerper lerp;

    tri_wheel.Initialize();
    tri_wheel.HomeLegs();
    sjsu::Delay(1s);
    sjsu::LogInfo("Starting control loop...");
    while (1)
    {
        // //For Mission Control Mode
        // std::string endpoint = mission_control.CreateGETRequestParameterWithRoverStatus();
        // std::string response = esp.GetCommands(endpoint);
        // commands = mission_control.ParseMissionControlData(response);

        // //For Manual Mode
        // commands = SerialEnterCommands();
        // commands.Print();
        // sjsu::Delay(50ms);
        commands = rules_engine.ValidateCommands(commands);
        commands = mode_switch.SwitchSteerMode(commands, arguments, motor_speeds);
        commands = lerp.Lerp(commands);
        arguments = ModeSelect::SelectMode(commands);
        arguments = tri_wheel.SetLegArguments(arguments);

        arguments.Print();
        motor_speeds.print();
        motor_speeds = tri_wheel.GetMotorFeedback();
    }

    return 0;
}