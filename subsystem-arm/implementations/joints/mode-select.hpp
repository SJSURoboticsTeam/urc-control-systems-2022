#pragma once

#include "../dto/arm-dto.hpp"
#include "../implementations/arm-modes.hpp"

namespace sjsu::arm
{

    inline arm_arguments SelectMode(arm_commands commands)
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
            return arm_arguments{};
            break;
        }
        }
    }

    
}