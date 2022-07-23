#include <cstdio>
#include <iterator>

#include "peripherals/lpc40xx/uart.hpp"
#include "utility/log.hpp"
#include "utility/time/time.hpp"

const char response_body_format[] =
    "\r\n\r\n{\n"
    "  \"drive_mode\": \"%c\",\n"
    "  \"speed\": %d,\n"
    "  \"angle\": %d\n"
    "  \"wheel_orientation\": %d,\n"
    "}";

int main()
{
    sjsu::LogInfo("Starting application...");
    auto &uart2 = sjsu::lpc40xx::GetUart<0>();
    uart2.settings.baud_rate = 38400;
    uart2.Initialize();

    while (1)
    {
<<<<<<< HEAD
        std::array<uint8_t, 64> receive_buffer;
        receive_buffer.fill(0);

        if (uart2.HasData())
        {
            const size_t kReadBytes = uart2.Read(receive_buffer);
            sjsu::LogInfo("(%zu) Bytes received: %.*s",
                          kReadBytes,
                          kReadBytes,
                          receive_buffer.data());
        }
        sjsu::Delay(1s);
=======
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
>>>>>>> b32eeb3bdb833588a123a3d852ad971b6c9f4e7c
    }
    return 0;
}