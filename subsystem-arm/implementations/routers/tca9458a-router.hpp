#pragma once
#include "utility/log.hpp"
#include "utility/math/units.hpp"
#include "devices/sensors/movement/accelerometer.hpp"

namespace sjsu::arm
{
    class tca9458
    {
        tca9458(sjsu::lpc40xx::I2c &i2c)
        {
            i2c.Initialize();
            buffer[0] = 1;
            i2c.Write(0x70,buffer);
        }

        void openBus(int a, sjsu::lpc40xx::I2c &i2c) 
        //bus translates to physical connection to the mux
        {
            if((a <= 7) || (a >= 0)){
                buffer[0] = static_cast <uint8_t> (pow(2,a));
                i2c.Write(0x70,buffer);
                sjsu::Delay(100ms);
            }
            else{
                sjsu::LogInfo("Invalid bus");
            }
        }

    private:
        std::array<uint8_t, 1> buffer = {0};
    };
}
