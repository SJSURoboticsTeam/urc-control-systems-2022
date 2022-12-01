#pragma once

#include "../dto/drive-dto.hpp"
#include "../implementations/steer-modes.hpp"

namespace sjsu::drive
{
    class ModeSelect
    {
    public:
        static tri_wheel_router_arguments SelectMode(drive_commands commands)
        {
            switch (commands.mode)
            {
            case 'D':
                return SteerModes::DriveSteering(commands);
                break;
            case 'S':
                return SteerModes::SpinSteering(commands);
                break;
            case 'T':
                return SteerModes::TranslateSteering(commands);
                break;
            case 'R':
                tri_wheel_router_arguments temp{};
                temp.mode = 'R';
                return temp;
                break;
            default:
                return tri_wheel_router_arguments{};
                break;
            }
        }

    private:
    };
}