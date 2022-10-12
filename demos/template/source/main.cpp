#include "utility/log.hpp"

#include "../../common/serial.hpp"

int main()
{
    sjsu::LogInfo("Starting demo application...");
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());

    return 0;
}