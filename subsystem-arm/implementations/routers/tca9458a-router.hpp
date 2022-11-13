#pragma once

#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"


namespace sjsu::arm
{
    class TCA9458A
    {
        public:
        TCA9458A(sjsu::lpc40xx::I2c &i2c) : i2c_(i2c)
        {
            buffer[0] = 1;
        }

        void OpenBus(int a) 
        //bus translates to physical connection to the mux
        {
            if((a <= 7) || (a >= 0)){
                buffer[0] = static_cast <uint8_t> (pow(2,a));
                i2c_.Write(0x70,buffer);
                sjsu::Delay(10ms);
            }
            else{
                sjsu::LogInfo("Invalid bus");
            }
        }

    private:
        std::array<uint8_t,1> buffer = {0};
        sjsu::lpc40xx::I2c &i2c_;
    };
}
