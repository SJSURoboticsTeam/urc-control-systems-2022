#include <cstdint>
#include "utility/log.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
#include "../../../subsystem-drive/implementations/homing-system.hpp"

int main()
{
    sjsu::LogInfo("Homing System Starting...");

    auto& left = sjsu::lpc40xx::GetGpio<2, 8>();
    auto& right = sjsu::lpc40xx::GetGpio<0, 16>();
    auto& back = sjsu::lpc40xx::GetGpio<1, 31>();

    sjsu::drive::HomingSystem::HomingMagnets magnets(left, right, back);
    sjsu::drive::HomingSystem magnet_router(magnets);
    magnet_router.Initialize();




    while (true)
    {
        magnet_router.PrintPins();
        magnet_router.ReadPins().left_gpio_.Read();
    }

    return 0;
}