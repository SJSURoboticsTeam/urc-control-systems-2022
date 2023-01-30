#include <cstdio>

#include "utility/log.hpp"
#include "utility/time/time.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc40xx/uart.hpp"
#include "devices/actuators/servo/rmd_x.hpp"
#include "peripherals/lpc40xx/gpio.hpp"

#include "../implementations/mission-control-handler.hpp"
#include "../implementations/steer-modes.hpp"
#include "../implementations/tri-wheel-router.hpp"
#include "../implementations/mode-switcher.hpp"
#include "../implementations/mode-select.hpp"
#include "../implementations/command-lerper.hpp"
#include "../implementations/rules-engine.hpp"
#include "../dto/motor-feedback-dto.hpp"
#include "../common/serial.hpp"
//#include "../common/esp.hpp"

using namespace sjsu::drive;

int main()
{
    // sjsu::common::Esp esp;
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
    sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
    sjsu::StaticMemoryResource<1024> memory_resource;
    sjsu::CanNetwork can_network(can, &memory_resource);

    // RMD addressesGetSerialCommands 0x141 - 0x148 are available
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

    auto &left_magnet = sjsu::lpc40xx::GetGpio<2, 1>();
    auto &right_magnet = sjsu::lpc40xx::GetGpio<2, 2>();
    auto &back_magnet = sjsu::lpc40xx::GetGpio<2, 0>();

    TriWheelRouter::leg right(right_steer_motor, right_hub_motor, right_magnet);
    TriWheelRouter::leg left(left_steer_motor, left_hub_motor, left_magnet);
    TriWheelRouter::leg back(back_steer_motor, back_hub_motor, back_magnet);

    TriWheelRouter tri_wheel{right, left, back};

    MissionControlHandler mission_control;
    drive_commands commands;
    motor_feedback motor_speeds;
    tri_wheel_router_arguments arguments;

    RulesEngine rules_engine;
    ModeSwitch mode_switch;
    CommandLerper lerp;

    tri_wheel.Initialize();
    sjsu::Delay(1s);
    //tri_wheel.HomeLegs();
    sjsu::LogInfo("Starting control loop...");
    sjsu::Delay(1s);
    //rules_engine.ValidateCommands(commands);

    while (1)
    {
        // For ESP
        // std::string endpoint = mission_control.CreateGETRequestParameterWithRoverStatus(commands);
        // std::string response = esp.GetCommands(endpoint);

        // For Serial
        std::string response = serial.GetCommands();
        if (response.find('{') != std::string::npos && response.find('}') != std::string::npos)
        {
            commands = mission_control.ParseMissionControlData(response);
            commands = rules_engine.ValidateCommands(commands);
            commands = mode_switch.SwitchSteerMode(commands, arguments, motor_speeds);
            commands = lerp.Lerp(commands);
       }
       commands.Print();
        arguments = ModeSelect::SelectMode(commands);
        arguments = tri_wheel.SetLegArguments(arguments);
        motor_speeds = tri_wheel.GetMotorFeedback();
        rules_engine.getHeartbeatRover();

        sjsu::LogInfo("Rover Heartbeat: %d", rules_engine.getHeartbeatRover());
    }
    
    return 0;
}