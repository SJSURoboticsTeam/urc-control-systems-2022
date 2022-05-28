

#include <cstdio>
#include <iterator>

#include "peripherals/lpc40xx/uart.hpp"
#include "utility/log.hpp"
#include "utility/time/time.hpp"
#include "utility/log.hpp"

const char response_body_format[] =
    "\r\n\r\n{\n"
    "  \"drive_mode\": \"%c\",\n"
    "  \"speed\": %d,\n"
    "  \"angle\": %d\n"
    "  \"wheel_orientation\": %d,\n"
    "}";

char mode;
int speed, angle, wheel_orientation;
char response[300] = R"({"drive_mode":"D","speed":68,"angle":0,"wheel_orientation":0})";

int main()
{
    sjsu::LogInfo("STDIN Application Starting...\n");

    sjsu::lpc40xx::Uart &uart2 = sjsu::lpc40xx::GetUart<2>();

    sjsu::LogInfo("Setting Baud rate to 38400");
    uart2.settings.baud_rate = 38400;
    uart2.Initialize();

    std::array<uint8_t, 32> receive_buffer;

    // Fill buffer with zeros
    receive_buffer.fill(0);

    // Read bytes into buffer until either the buffer is full or the UART
    // peripheral no longer has any more bytes left.
    // Store bytes into the kReadBytes variable.
    const size_t kReadBytes = uart2.Read(receive_buffer);

    // Print out the number of bytes read and the actual buffer
    sjsu::LogInfo("(%zu) Bytes received: %.*s",
                  kReadBytes,
                  kReadBytes,
                  receive_buffer.data());

    sscanf(
        response, response_body_format,
        &mode, &speed, &angle,
        &wheel_orientation);

    printf("\n--> Mode %c \n--> Speed %d \n--> Angle %d \n--> Wheel_orientation %d\n", mode, speed, angle, wheel_orientation);

    return 0;
}