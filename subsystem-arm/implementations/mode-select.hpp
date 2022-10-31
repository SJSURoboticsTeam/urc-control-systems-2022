#pragma once

#include "arm-modes.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class HandModeSelect
    {
    public:
        static hand_arguments SelectMode(hand_arguments commands)
        {
            switch (commands.mode)
            {
            case 'S':
                return HandModes::SimultaneousMode(commands);
                break;
            default:
                return commands;
                break;
            }
        }
    };

    class JointModeSelect
    {
    public:
        static joint_arguments SelectMode(joint_arguments commands)
        {
            switch (commands.mode)
            {
            case 'S':
            {
                return JointModes::SimultaneousMode(commands);
                break;
            }
            case 'C':
            {
                return JointModes::CondensedMode(commands);
                break;
            }
            default:
            {
                return joint_arguments{};
                break;
            }
            }
        }
    };
}