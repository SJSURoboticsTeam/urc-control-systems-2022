#pragma once
#include "../dto/drive-dto.hpp"
#include "../dto/motor-feedback-dto.hpp"

namespace sjsu::drive
{
    class WheelShifter
    {
    public:
        // Should handle all the logic for switching to new steer mode
        drive_commands ShiftWheel(drive_commands commands, tri_wheel_router_arguments previous_arguments, motor_feedback current_motor_feedback)
        {
            bool hubs_stopped(previous_arguments.left.hub.speed == 0 && previous_arguments.right.hub.speed == 0 && previous_arguments.back.hub.speed == 0);
            bool steers_stopped(current_motor_feedback.left_steer_speed == 0_rpm && current_motor_feedback.right_steer_speed == 0_rpm && current_motor_feedback.back_steer_speed == 0_rpm);
            if (previous_mode_ != commands.mode)
            {
                while_shifting = true;
                skip_once_ = true;
            }
            if (while_shifting)
            {
                commands.speed = 0;
                if (!hubs_stopped)
                {
                    commands.mode = previous_mode_;
                    return commands;
                } // hubs must be stopped to pass here
                else if (!skip_once_ && steers_stopped)
                {
                    while_shifting = false;
                    skip_once_ = true;
                } // only once steer motors have stopped moving after hubs stopped will we exit switching modes
                previous_mode_ = commands.mode;
                skip_once_ = false;
            }
            return commands;
        }

    private:
        char previous_mode_ = 'D';
        bool while_shifting = true;
        bool skip_once_ = true;
    };
}