#pragma once

#include <cinttypes>
#include <cstdint>

#include "utility/log.hpp"
#include "peripherals/lpc40xx/uart.hpp"
#include "devices/communication/esp8266.hpp"

namespace sjsu::common
{
    class Esp
    {
    public:
        Esp()
            : esp_(sjsu::lpc40xx::GetUart<3>()),
              wifi_(esp_.GetWiFi()),
              socket_(esp_.GetInternetSocket())
        {
            esp_.Initialize();
        };

        void Connect()
        {
            try
            {
                sjsu::LogInfo("Connecting to %s...", kSsid);
                wifi_.ConnectToAccessPoint(kSsid, kPassword, kDefaultTimeout);
                sjsu::LogInfo("Connecting to Socket...");
                socket_.Connect(sjsu::InternetSocket::Protocol::kTCP, kUrl, kPort, kDefaultTimeout);
                sjsu::LogInfo("Connected!");
            }
            catch (const std::exception &e)
            {
                sjsu::LogError("Error connecting to Wifi!");
            }
        }

        void Disconnect()
        {
            try
            {
                sjsu::LogInfo("Disconnecting from Socket...");
                socket_.Close();
                sjsu::LogInfo("Disconnecting from Wifi...");
                wifi_.DisconnectFromAccessPoint();
                sjsu::LogInfo("Disconnected!");
            }
            catch (const std::exception &e)
            {
                sjsu::LogError("Error disconnecting from Wifi!");
            }
        }

        std::string GetCommands(char *endpoint)
        {
            std::array<uint8_t, 1024 * 2> raw_response;
            std::fill(raw_response.begin(), raw_response.end(), 0);

            char request[200];
            snprintf(request, sizeof(request), "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", endpoint, kUrl);

            std::span request_payload(reinterpret_cast<const uint8_t *>(request), sizeof(request));

            try
            {
                socket_.Write(request_payload, kDefaultTimeout);
                size_t response_size = socket_.Read(raw_response, kDefaultTimeout);
                std::string str_response(reinterpret_cast<char *>(raw_response.data()), response_size);
                return str_response;
            }
            catch (const std::exception &e)
            {
                sjsu::LogError("Error writing/reading commands!");
                Disconnect();
                Connect();
                return "";
            }
        }

    private:
        sjsu::Esp8266 esp_;
        sjsu::WiFi &wifi_;
        sjsu::InternetSocket &socket_;
        const uint16_t kPort = 5000;
        const char *kUrl = "192.168.1.28";
        const char *kSsid = "Izzys 2.4GHz";
        const char *kPassword = "Nezzy559";
        std::chrono::seconds kDefaultTimeout = 5s;
    };
} // namespace sjsu::common