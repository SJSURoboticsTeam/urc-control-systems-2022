#pragma once
#include "../dto/drive-dto.hpp"
#include "../implementations/steer-modes.hpp"

namespace sjsu::drive
{
    class ModeSwitch
    {
    public:
        // Should handle all the logic for switching to new steer mode
        drive_commands SwitchSteerMode(drive_commands commands, tri_wheel_router_arguments previous_arguments)
        {
            bool stopped(previous_arguments.left.hub.speed == 0 && previous_arguments.right.hub.speed == 0 && previous_arguments.back.hub.speed == 0);
            if (previous_mode_ != commands.mode)
            {
                // Set all wheel speed equal to 0
                commands.speed = 0;
                commands.angle = 0;
                commands.wheel_orientation = 0;
                // Set rover to home position using home function
            }
            if (!stopped && previous_mode_ != commands.mode)
            {
                commands.mode = previous_mode_;
            }
            else
            {
                previous_mode_ = commands.mode;
            }

            return commands;
        }

    private:
        char previous_mode_ = 'D';
    };
}