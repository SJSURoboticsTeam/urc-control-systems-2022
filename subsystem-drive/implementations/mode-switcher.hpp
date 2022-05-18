#pragma once
#include "../dto/drive-dto.hpp"
#include "../dto/motor-feedback-dto.hpp"

namespace sjsu::drive
{
    class ModeSwitch
    {
    public:
        // Should handle all the logic for switching to new steer mode
        drive_commands SwitchSteerMode(drive_commands commands, tri_wheel_router_arguments previous_arguments, motor_feedback current_motor_feedback)
        {
            bool hubs_stopped(previous_arguments.left.hub.speed == 0 && previous_arguments.right.hub.speed == 0 && previous_arguments.back.hub.speed == 0);
            bool steers_stopped(current_motor_feedback.left_steer_speed == 0_rpm && current_motor_feedback.right_steer_speed == 0_rpm && current_motor_feedback.back_steer_speed == 0_rpm);
            if (previous_mode_ != commands.mode || switching_modes)
            {
                // Set all wheel speed equal to 0
                commands.speed = 0;
                commands.angle = 0;
                commands.wheel_orientation = 0;
                // Set rover to home position using home function
            }
            if (hubs_stopped)
            {
                //if hubs are stopped and steers are not stopped then we are switching modes, but if hubs are stopped and steers are stopped, then we are not switching modes
                !steers_stopped ? switching_modes = true : switching_modes = false;
            }
            if (!hubs_stopped && previous_mode_ != commands.mode)
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
        char previous_mode_ = 'D'; // set to O to represent off in the beginning
        bool switching_modes = true;
    };
}