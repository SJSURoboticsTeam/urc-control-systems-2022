#pragma once

namespace sjsu::drive
{
    // note: postfix commands and arguments can be seperated into different files
    struct drive_commands
    {
        char mode = 'D';
        int speed = 0; // -100 <--> 100
        int angle = 0; // -180 <--> 180
        int wheel_orientation = 0;

        void Print()
        {
            printf("Cmds\tMode\tSpeed\tAngle\tOri\n");
            printf("\t%c\t%d\t%d\t%d\n", mode, speed, angle, wheel_orientation);
        }
    };

    struct motor_arguments
    {
        float speed = 0;
        float angle = 0;
    };

    struct leg_arguments
    {
        motor_arguments steer{motor_arguments{5, 0}};
        motor_arguments hub;
    };

    struct tri_wheel_router_arguments
    {
        leg_arguments left{};
        leg_arguments right{};
        leg_arguments back{};

        void Print()
        {
            printf("Args\tLeg\tSpeed\tAngle\n");
            printf("\tLeft\t%.1f\t%.1f\n", static_cast<double>(left.hub.speed), static_cast<double>(left.steer.angle));
            printf("\tRight\t%.1f\t%.1f\n", static_cast<double>(right.hub.speed), static_cast<double>(right.steer.angle));
            printf("\tBack\t%.1f\t%.1f\n", static_cast<double>(back.hub.speed), static_cast<double>(back.steer.angle));
        }
    };

} // sjsu::drive
