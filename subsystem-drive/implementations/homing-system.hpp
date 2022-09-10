#pragma once
#include "peripherals/lpc40xx/gpio.hpp"
#include "utility/math/units.hpp"
#include "utility/log.hpp"

#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class HomingSystem
    {
    public:
        struct HomingMagnets
        {
            HomingMagnets(sjsu::Gpio &left_gpio, sjsu::Gpio &right_gpio, sjsu::Gpio &back_gpio)
                : left_gpio_(left_gpio), right_gpio_(right_gpio), back_gpio_(back_gpio)
            {
            }
            // todo change pins and ports
            sjsu::Gpio &left_gpio_;
            sjsu::Gpio &right_gpio_;
            sjsu::Gpio &back_gpio_;
        };

        HomingSystem(HomingMagnets magnets) : magnets_(magnets)
        {
        }
        void Initialize()
        {
            magnets_.left_gpio_.Initialize();
            magnets_.right_gpio_.Initialize();
            magnets_.back_gpio_.Initialize();

            SetInput();
        }

        // temp returns status
        HomingMagnets ReadPins()
        {
            return magnets_;
        }

        void PrintPins()
        {
            sjsu::LogInfo("Left Pin is currently %d", magnets_.left_gpio_.Read());
            sjsu::LogInfo("Right Pin is currently %d", magnets_.right_gpio_.Read());
            sjsu::LogInfo("Back Pin is currently %d", magnets_.back_gpio_.Read());
        }

        HomingMagnets magnets_;

    private:
        void SetInput()
        {
            magnets_.left_gpio_.SetAsInput();
            magnets_.right_gpio_.SetAsInput();
            magnets_.back_gpio_.SetAsInput();
        }
    };
}