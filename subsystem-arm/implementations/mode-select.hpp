#pragma once

#include "arm-modes.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    class ModeSelect
    {
        public:
            // we take arm_args as reference in the handmodes so that way they dont override the values previously assigned
            static arm_arguments SelectMode(mc_commands commands, arm_arguments arm_args)
            {
                switch (commands.mode)
                {
                    case 'H':
                        return Mode::Hand(commands, arm_args);
                        break;
                    case 'J':
                        return Mode::Joint(commands, arm_args);
                        break;
                    case 'R':
                        return Mode::RRNine(commands, arm_args);
                        break;
                    default:
                        return arm_args;
                        break;
                }
            }

        private:
    };
}