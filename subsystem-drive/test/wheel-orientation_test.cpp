#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "implementations/wheel-orientation.hpp"

namespace sjsu::drive {
    TEST_CASE("Tri wheel router testing")
    {
        SECTION("")
        {
            WheelOrientation pos;
            tri_wheel_router_arguments orig;
            tri_wheel_router_arguments news = pos.step_up(1);

            CHECK_EQ(orig.left, news.right);
            CHECK_EQ(orig.right, news.back);
            CHECK_EQ(orig.back, news.left);

            news = pos.step_down(1);

            CHECK_EQ(orig.left, news.left);
            CHECK_EQ(orig.right, news.right);
            CHECK_EQ(orig.back, news.back);



            


        }
    }
}