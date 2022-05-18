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
            if (previous_mode_ != commands.mode)
            {
                in_the_middle_of_switchingmodes_ = true;
                skip_once_ = true;
            }
            if (in_the_middle_of_switchingmodes_)
            {
                commands.speed = 0;
                if (!hubs_stopped)
                {
                    commands.mode = previous_mode_;
                    return commands;
                } // hubs must be stopped to pass here
                else if (skip_once_ && steers_stopped)
                {
                    skip_once_ = false;
                } // will start moving steer motors before exiting middle of switching modes
                else if (steers_stopped)
                {
                    in_the_middle_of_switchingmodes_ = false;
                    skip_once_ = true;
                } // only once steer motors have stopped moving after hubs stopped will we exit switching modes
                previous_mode_ = commands.mode;
            }
            return commands;
        }

    private:
        char previous_mode_ = 'D';
        bool in_the_middle_of_switchingmodes_ = true;
        bool skip_once_ = true;
    };
}