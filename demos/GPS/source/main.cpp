#include <cstdio>
#include <iterator>

#include "peripherals/lpc40xx/uart.hpp"
#include "utility/log.hpp"
#include "utility/time/time.hpp"

//Using pins TX 4.28 and RX 4.29, 3.3V and GND

int main()
{
  sjsu::LogInfo("GPS connection starting...");
  auto & uart2 = sjsu::lpc40xx::GetUart<3>();
  uart2.settings.baud_rate = 9600;
  uart2.Initialize();

  while (true)
  {
    std::array<uint8_t, 1024 * 3> receive_buffer;
    receive_buffer.fill(0);
    const size_t kReadBytes = uart2.Read(receive_buffer);

    printf("\n\n(%zu) GPS Data Received:\n\n%.*s",
                  kReadBytes,
                  kReadBytes,
                  receive_buffer.data());

    sjsu::Delay(1s);
  }
  return 0;
}
