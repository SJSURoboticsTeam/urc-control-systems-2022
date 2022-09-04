#include <cstdio>
#include <iterator>

#include "utility/log.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc40xx/uart.hpp"
#include "devices/actuators/servo/rmd_x.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
//#include "../common/esp.hpp"

// #include "../implementations/mission-control-handler.hpp"
#include "../implementations/steer-modes.hpp"
#include "../implementations/tri-wheel-router.hpp"
#include "../implementations/mode-switcher.hpp"
#include "../implementations/mode-select.hpp"
#include "../implementations/command-lerper.hpp"
#include "../implementations/rules-engine.hpp"
#include "../dto/motor-feedback-dto.hpp"
#include "utility/time/time.hpp"

using namespace sjsu::drive;

const char response_body_format[] =
    "\r\n\r\n{\n"
    "  \"drive_mode\": \"%c\",\n"
    "  \"speed\": %d,\n"
    "  \"angle\": %d\n"
    "  \"wheel_orientation\": %d,\n"
    "}";

drive_commands ParseMissionControlData(std::string &response, drive_commands commands)
{
    int actual_arguments = sscanf(
        response.c_str(), response_body_format,
        &commands.mode, &commands.speed, &commands.angle, &commands.wheel_orientation);
    return commands;
}

drive_commands HandleWebInteractions(sjsu::lpc40xx::Uart &uart2, std::array<uint8_t, 1024 * 2> &receive_buffer, drive_commands commands) {
    sjsu::Delay(50ms);
    printf("{\"subsystem\":\"drive\",\"speed\":%d,\"angle\":%d,\"drive_mode\":\"%c\",\"wheel_orientation\":%d}\n", commands.speed, commands.angle, commands.mode, commands.wheel_orientation);
    std::fill(receive_buffer.begin(), receive_buffer.end(), 0);
    if (uart2.HasData())
    {
        const size_t kReadBytes = uart2.Read(receive_buffer, 50ms);
        std::string message(reinterpret_cast<char *>(receive_buffer.data()), kReadBytes);
         commands = ParseMissionControlData(message, commands);
    }
    return commands;
}


// drive_commands SerialEnterCommands()
// {
//     drive_commands commands;
//     sjsu::LogInfo("Enter in commands");
//     scanf("%d,%d,%c", &commands.speed, &commands.angle, &commands.mode);
//     return commands;
// }

int main()
{
    auto &uart2 = sjsu::lpc40xx::GetUart<0>();
    uart2.settings.baud_rate = 38400;
    std::array<uint8_t, 1024 * 2> receive_buffer;

    //sjsu::common::Esp esp;
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

    auto& left_magnet = sjsu::lpc40xx::GetGpio<2, 1>();
    auto& right_magnet = sjsu::lpc40xx::GetGpio<2, 2>();
    auto& back_magnet = sjsu::lpc40xx::GetGpio<2, 0>();

    TriWheelRouter::leg right(right_steer_motor, right_hub_motor, right_magnet);
    TriWheelRouter::leg left(left_steer_motor, left_hub_motor, left_magnet);
    TriWheelRouter::leg back(back_steer_motor, back_hub_motor, back_magnet);

    TriWheelRouter tri_wheel{right, left, back};

    // MissionControlHandler mission_control;
    drive_commands commands;
    motor_feedback motor_speeds;
    tri_wheel_router_arguments arguments;

    RulesEngine rules_engine;
    ModeSwitch mode_switch;
    CommandLerper lerp;

    uart2.Initialize();
    tri_wheel.Initialize();
    sjsu::Delay(1s);
    tri_wheel.HomeLegs();
    sjsu::Delay(1s);
    // sjsu::LogInfo("Starting control loop...");

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
        // commands = HandleWebInteractions(uart2, receive_buffer, commands);
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