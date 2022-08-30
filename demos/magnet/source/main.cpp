#include <cstdint>
#include "utility/log.hpp"
#include "peripherals/lpc40xx/gpio.hpp"

int main()
{
    sjsu::LogInfo("Magnet Tester Starting...");

    sjsu::Gpio &magnet = sjsu::lpc40xx::GetGpio<1, 31>();

    magnet.Initialize();
    magnet.SetAsInput();

    while (true){
        sjsu::LogInfo("Magnet is currently %d", magnet.Read());
    }

    return 0;
}