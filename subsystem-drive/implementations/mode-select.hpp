#pragma once

#include "../dto/drive-dto.hpp"
#include "../implementations/steer-modes.hpp"

namespace sjsu::drive
{
    class ModeSelect
    {
    public:
        static tri_wheel_router_arguments SelectMode(drive_commands commands, motor_feedback steer_motor_data)
        {
            switch (commands.mode)
            {
            case 'D':
                return SteerModes::DriveSteering(commands, steer_motor_data);
                break;
            case 'S':
                return SteerModes::SpinSteering(commands);
                break;
            case 'T':
                return SteerModes::TranslateSteering(commands);
                break;
            default:
                return tri_wheel_router_arguments{};
                break;
            }
        }

    private:
    };
}