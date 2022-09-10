#include <cstdint>
#include "utility/log.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
#include "../../../subsystem-drive/implementations/homing-system.hpp"

int main()
{
    sjsu::LogInfo("Homing System Starting...");

    auto& left = sjsu::lpc40xx::GetGpio<2, 1>();
    auto& right = sjsu::lpc40xx::GetGpio<2, 2>();
    auto& back = sjsu::lpc40xx::GetGpio<2, 0>();

    left.SetAsInput();
    right.SetAsInput();
    back.SetAsInput();

    left.Initialize();
    right.Initialize();
    back.Initialize();

    while (true)
    {
        sjsu::LogInfo("Left Pin:%d", left.Read());
        sjsu::LogInfo("Right Pin:%d", right.Read());
        sjsu::LogInfo("Back Pin:%d", back.Read());
    }

    return 0;
}