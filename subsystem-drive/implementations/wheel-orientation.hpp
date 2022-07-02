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

        tri_wheel_router_arguments step_up(int pos){

        }
        tri_wheel_router_arguments step_down(int pos){

        }

        private:
        tri_wheel_router_arguments ligma;
        int position = 0;
    };
}