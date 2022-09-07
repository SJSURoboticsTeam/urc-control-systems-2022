#include "peripherals/lpc40xx/uart.hpp"
#include "../subsystem-drive/dto/drive-dto.hpp"
#include "utility/log.hpp"

namespace sjsu::common
{
    class Serial
    {
    public:
        Serial(sjsu::Uart &uart) : uart_(uart)
        {
            Initialize();
        };

        std::string GetSerialCommands()
        {
            std::fill(receive_buffer.begin(), receive_buffer.end(), 0);
            sjsu::Delay(50ms);
            if (uart_.HasData())
            {
                const size_t kReadBytes = uart_.Read(receive_buffer, 50ms);
                std::string message(reinterpret_cast<char *>(receive_buffer.data()), kReadBytes);
                return message;
            }
            return "";
        }

    private:
        void Initialize()
        {
            uart_.settings.baud_rate = 38400;
            uart_.Initialize();
        }
        std::array<uint8_t, 1024 * 2> receive_buffer;
        sjsu::Uart &uart_;
    };
} // namespace sjsu::common