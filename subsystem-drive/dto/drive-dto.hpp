#pragma once
namespace sjsu::drive
{   
    //note: postfix commands and arguments can be seperated into different files
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
            int angle = 0;
            int speed = 0;
        };
        motor_arguments steering{};
        motor_arguments velocity{};
    };

    struct tri_wheel_router_arguments
    {
        leg_arguments a{};
        leg_arguments b{};
        leg_arguments c{};
    };
} // sjsu::drive