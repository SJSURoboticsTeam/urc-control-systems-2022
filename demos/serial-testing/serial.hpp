#pragma once

#include "utility/log.hpp"
#include "peripherals/lpc40xx/uart.hpp"

namespace sjsu::common
{
    class Serial
    {
    public:
        Serial(sjsu::Uart &uart) : uart_(uart)
        {
            Initialize();
        };

        std::string GetCommands()
        {
            std::array<uint8_t, 1024 * 2> raw_response;
            std::fill(raw_response.begin(), raw_response.end(), 0);
            if (uart_.HasData())
            {
                const size_t response_size = uart_.Read(raw_response, 50ms);
                std::string str_response(reinterpret_cast<char *>(raw_response.data()), response_size);
                return str_response;
            }
            return "";
        }

    private:
        void Initialize()
        {
            uart_.settings.baud_rate = 38400;
            uart_.Initialize();
        }
        sjsu::Uart &uart_;
    };
} // namespace sjsu::common