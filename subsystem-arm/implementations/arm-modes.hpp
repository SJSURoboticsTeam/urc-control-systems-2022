#pragma once

#include "../dto/arm-dto.hpp"

namespace sjsus::arm
{
    class ArmModes
    {
        public:

        static arm_arguments SimulataneousMode(arm_commands commands)
        {}

        static arm_arguments CondensedMode(arm_commands commands)
        {}
        //TODO: come up with other possible modes
    };
}