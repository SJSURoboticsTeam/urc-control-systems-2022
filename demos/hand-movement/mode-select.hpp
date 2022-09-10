#pragma once
#include "../arm-dto.hpp"
#include "../hand-modes.hpp"
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
                return HandModes::CloseHand(commands);
                break;
            case 'O':
                return HandModes::OpenHand(commands);
                break;
            case 'I':
                return HandModes::IndividualHand(commands);
                break;
            case 'S':
                return HandModes::SimultaneousHand(commands);
                break;
            default:
                break;
            }
        }

    private:
    };
}