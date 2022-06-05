#pragma once

#include "../dto/arm-dto.hpp"
#include "../implementations/arm-modes.hpp"

namespace sjsu::arm
{

    class ModeSelect
    {
    public:
        static arm_arguments SelectMode(arm_commands commands)
        {
            switch (commands.mode)
            {
                case 'S':
                {
                    return ArmModes::SimulataneousMode(commands);
                    break;
                }
                case 'C':
                {   
                    return ArmModes::CondensedMode(commands);
                    break;
                }
                default:
                {
                    return arm_arguments{};
                    break;
                }
            }
        }
    };
}