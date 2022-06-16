#include <cstdio>

#include "peripherals/lpc40xx/uart.hpp"
#include "utility/log.hpp"
#include "utility/time/time.hpp"
#include "utility/log.hpp"

int main()
{
    sjsu::LogInfo("Starting application...");
    sjsu::lpc40xx::Uart &uart2 = sjsu::lpc40xx::GetUart<0>();
    uart2.settings.baud_rate = 38400;
    uart2.Initialize();

    while (1)
    {
        std::array<uint8_t, 32> receive_buffer;
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
    }
    return 0;
}