#pragma once
#include "../dto/drive-dto.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"
#include "peripherals/lpc40xx/gpio.hpp"

namespace sjsu::drive
{
    class MagnetRouter
    {
        public MagnetRouter(sjsu::Gpio &left_gpio, sjsu::Gpio &right_gpio, sjsu::Gpio &back_gpio)
           : left_gpio_(left_gpio), right_gpio_(right_gpio), back_gpio_(back_gpio)
           {

           }
        void Initialize()
        {
            left_gpio_.Initialize();
            right_gpio_.Initialize();
            back_gpio_.Initialize();
        }

        //temp returns status
        void ReadPins()
        {
            left_gpio_.Read();
            right_gpio_.Read();
            back_gpio_.Read();
        }
       
    
    private :

        void SetInput()
        {
            left_gpio_.SetAsInput();
            right_gpio_.SetAsInput();
            back_gpio_.SetAsInput();
        }
        //todo change pins and ports
        sjsu::Gpio left_gpio_ = sjsu::lpc40xx::GetGpio<1, 19>();
        sjsu::Gpio right_gpio_ = sjsu::lpc40xx::GetGpio<1, 19>();
        sjsu::Gpio back_gpio_ = sjsu::lpc40xx::GetGpio<1, 19>();




    }
}