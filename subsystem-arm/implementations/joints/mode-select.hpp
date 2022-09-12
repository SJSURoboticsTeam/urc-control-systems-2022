#pragma once

#include "../dto/arm-dto.hpp"
#include "./joint-modes.hpp"

namespace sjsu::arm
{

    class ModeSelect
    {
    public:
        static joint_arguments SelectMode(joint_arguments commands)
        {
            switch (commands.mode)
            {
            case 'S':
            {
                return JointModes::SimulataneousMode(commands);
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