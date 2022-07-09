/*
IDEAS:

Switch leg args. in tri addresses
pass new tri. variable (must be able to run all the time)
create a temp leg arg pass same tri. ad.

*/
#pragma once
#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class WheelOrientation
    {
        public:
        WheelOrientation ()
        {
            previous_pos_ = 0;
        }
        /*works the form position 0-2, though I believe every time we start up our code i
        t sets it's current position to 0. */
        tri_wheel_router_arguments switch_to(tri_wheel_router_arguments command) 
        {   
            int pos = command.wheel_orientation;
            pos = pos % 3; // adds a layer of safety so that we don't end up passing to position 3k
            printf("Postion: %d\n",previous_pos_);

            // if (pos >= previous_pos_){
                for(int i = 0; i < pos; i++){
                    command = step_up(command);
                    printf("stepping up\n");
                }
            // }
            // else if(pos < previous_pos_){
            //     for(int i = 0; i < previous_pos_ - pos; i++){
            //         command = step_down(command);  
            //         printf("stepping down\n");
            //     }
            // }
            previous_pos_ = pos;
            return command;
        }
        int get_position(){
            return previous_pos_;
        }
        private:
        int previous_pos_;

        tri_wheel_router_arguments step_up(tri_wheel_router_arguments ligma){
            leg_arguments temp;
            temp = ligma.back;
            ligma.back = ligma.right;
            ligma.right = ligma.left;
            ligma.left = temp;

            return ligma;
        }
        tri_wheel_router_arguments step_down(tri_wheel_router_arguments ligma){
            //here handles the swiching logic
            leg_arguments temp;
            temp = ligma.back;
            ligma.back = ligma.left;
            ligma.left = ligma.right;
            ligma.right = temp;

            return ligma;
        }
    };
}