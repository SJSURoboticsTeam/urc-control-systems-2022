#pragma once
#include "dto/hand-dto.hpp"

namespace sjsu::arm
{
    class HandModes
    {
    public:
        HandModes(){};

        std::chrono::microseconds AngleToPulseWidth(int angle)
        {
            return std::chrono::microseconds(angle * (4096 / 360));
        }
    };
}