#pragma once

#include <string_view>

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
              socket_(esp_.GetInternetSocket()) { esp_.Initialize(); };

        void Connect()
        {
            ConnectToWifi();
            ConnectToWebServer();
        }

        void Disconnect()
        {
            wifi_.DisconnectFromAccessPoint();
        }

        std::string GetCommands(std::string request)
        {
            try
            {
                request = "GET /drive?param=0 HTTP/1.1\r\nHost: " + kUrl + "\r\n\r\n";
                std::span request_payload(
                    reinterpret_cast<const uint8_t *>(request.data()), request.size());
                socket_.Write(request_payload, kDefaultTimeout);
                std::array<uint8_t, 1024 * 2> raw_response;
                std::fill(raw_response.begin(), raw_response.end(), 0);
                size_t read_back = socket_.Read(raw_response, kDefaultTimeout);
                std::string str_response(reinterpret_cast<char *>(raw_response.data()), read_back);
                return str_response;
            }
            catch (const std::exception &e)
            {
                sjsu::LogError("Error getting commands!");
            }
        }

    private:
        void ConnectToWifi()
        {
            try
            {
                printf("Attempting to connect to %s...", kSsid);
                while (!wifi_.ConnectToAccessPoint(kSsid, kPassword, kDefaultTimeout))
                {
                    printf(".");
                }
                printf(" Connected!\n");
            }
            catch (const std::exception &e)
            {
                sjsu::LogError("Error connecting to wifi!");
            }
        }

        void ConnectToWebServer()
        {
            try
            {
                sjsu::LogInfo("Connecting to web server: %s:%s...", kUrl, kPort);
                socket_.Connect(sjsu::InternetSocket::Protocol::kTCP, kUrl,
                                static_cast<uint16_t>(kPort), kDefaultTimeout);
            }
            catch (const std::exception &e)
            {
                sjsu::LogError("Error connecting to server!");
            }
        }

        sjsu::Esp8266 esp_;
        sjsu::WiFi &wifi_;
        sjsu::InternetSocket &socket_;
        const uint16_t kPort = 5000;
        const std::string kUrl = "172.23.163.9";
        const std::string kSsid = "wifi name";
        const std::string kPassword = "wifi password";
        std::chrono::seconds kDefaultTimeout = 10s;
    };
} // namespace sjsu::common
