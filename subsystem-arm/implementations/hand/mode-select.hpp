#pragma once
#include "dto/arm-dto.hpp"
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
            case 'C':
                return HandModes::CloseMode(commands);
                break;
            case 'O':
                return HandModes::OpenMode(commands);
                break;
            case 'I':
                return HandModes::IndividualMode(commands);
                break;
            case 'S':
                return HandModes::SimultaneousMode(commands);
                break;
            default:
                break;
            }
        }

    private:
    };
}