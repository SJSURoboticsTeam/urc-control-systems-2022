#include <cstdint>

#include "utility/log.hpp"
#include "peripherals/lpc40xx/uart.hpp"
#include "peripherals/lpc40xx/gpio.hpp"

#include "../../common/serial.hpp"
#include "../../subsystem-drive/dto/drive-dto.hpp"
#include "../../subsystem-arm/dto/arm-dto.hpp"

sjsu::arm::arm_arguments arm_args;
sjsu::drive::drive_commands drive_args;

int main()
{
    sjsu::LogInfo("Starting serial testing demo...");
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
    while (true)
    {
        std::string response = serial.GetCommands();
        if (response.find('{') != std::string::npos && response.find('}') != std::string::npos)
        {
            sjsu::LogInfo("JSON Response: %s", response.c_str());
        }
    }
    return 0;
}