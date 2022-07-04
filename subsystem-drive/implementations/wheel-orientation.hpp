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
        WheelOrientation (tri_wheel_router_arguments init)
        {
            position = 0;
            ligma = init;
        }
        /*works the form position 0-2, though I believe every time we start up our code i
        t sets it's current position to 0. */
        tri_wheel_router_arguments switch_to(int pos) 
        {   
            pos = pos % 3; // adds a layer of safety so that we don't end up passing to position 3k
            printf("Postion: %d\n",position);

            if (pos > position){
                for(int i = 0; i < pos-position; i++){
                    step_up();
                }
            }else if(pos < position){
                for(int i = 0; i < position - pos; i++){
                    step_down();  
                }
            }
            position = pos;
            return ligma;
        }

        private:
        tri_wheel_router_arguments ligma;
        void step_up(){
            leg_arguments temp;
            temp = ligma.back;
            ligma.back = ligma.right;
            ligma.right = ligma.left;
            ligma.left = temp;

        }
        tri_wheel_router_arguments step_down(){
            //here handles the swiching logic
            leg_arguments temp;
            temp = ligma.back;
            ligma.back = ligma.left;
            ligma.left = ligma.right;
            ligma.right = temp;
 
        }
        int position;
    };
}