#pragma once
namespace sjsu::drive
{
    // note: postfix commands and arguments can be seperated into different files
    struct drive_commands
    {
        int angle = 0; // -180 <--> 180
        int speed = 0; // -100 <--> 100
        int wheel_orientation = 0;
        char mode = 'D';
    };

    struct leg_arguments
    {
        struct motor_arguments
        {
            float angle = 0;
            float speed = 0;
        };
        motor_arguments steer{};
        motor_arguments hub{};
    };

    struct tri_wheel_router_arguments
    {
        leg_arguments left{};
        leg_arguments right{};
        leg_arguments back{};
    };
} // sjsu::drive
