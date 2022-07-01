#pragma once
#include "dto/hand-dto.hpp"
#include "hand-modes.hpp"

namespace sjsu::arm
{
    class ModeSelect
    {
    public:
        static hand_arguments SelectMode(hand_arguments commands)
        {
            switch (commands.mode)
            {
            case 'A':
                return HandModes::CloseHand(commands);
                break;
            case 'B':
                return HandModes::OpenHand(commands);
                break;
            case 'C':
                return HandModes::PointHand(commands);
                break;
            case 'M':
                return HandModes::ManualHand(commands);
                break;
            default:
                break;
            }
        }

    private:
    };
}