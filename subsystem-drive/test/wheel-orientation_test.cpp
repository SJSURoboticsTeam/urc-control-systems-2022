#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "implementations/wheel-orientation.hpp"

namespace sjsu::drive {
    TEST_CASE("Tri wheel router testing")
    {
        SECTION("Testing postion 0 - 2")
        {
            tri_wheel_router_arguments orig{};
            orig.left.hub.speed = 25;
            WheelOrientation pos(orig);
            tri_wheel_router_arguments news = pos.switch_to(1);
            printf("Test case: 1 \nOriginal:");
            orig.Print();
            printf("New:");
            news.Print();

            CHECK_EQ(orig.left.hub.speed, news.right.hub.speed);
            CHECK_EQ(orig.left.hub.angle, news.right.hub.angle);
            CHECK_EQ(orig.left.steer.speed, news.right.steer.speed);
            CHECK_EQ(orig.left.steer.angle, news.right.steer.angle);
            
            CHECK_EQ(orig.right.hub.speed, news.back.hub.speed);
            CHECK_EQ(orig.right.hub.angle, news.back.hub.angle);
            CHECK_EQ(orig.right.steer.speed, news.back.steer.speed);
            CHECK_EQ(orig.right.steer.angle, news.back.steer.angle);

            CHECK_EQ(orig.back.hub.speed, news.left.hub.speed);
            CHECK_EQ(orig.back.hub.angle, news.left.hub.angle);
            CHECK_EQ(orig.back.steer.speed, news.left.steer.speed);
            CHECK_EQ(orig.back.steer.angle, news.left.steer.angle);

            news = pos.switch_to(0);
            printf("Test case: 0 \nOriginal:");
            orig.Print();
            printf("New:");
            news.Print();

            CHECK_EQ(orig.left.hub.speed, news.left.hub.speed);
            CHECK_EQ(orig.left.hub.angle, news.left.hub.angle);
            CHECK_EQ(orig.left.steer.speed, news.left.steer.speed);
            CHECK_EQ(orig.left.steer.angle, news.left.steer.angle);

            CHECK_EQ(orig.right.hub.speed, news.right.hub.speed);
            CHECK_EQ(orig.right.hub.angle, news.right.hub.angle);
            CHECK_EQ(orig.right.steer.speed, news.right.steer.speed);
            CHECK_EQ(orig.right.steer.angle, news.right.steer.angle);

            CHECK_EQ(orig.back.hub.speed, news.back.hub.speed);
            CHECK_EQ(orig.back.hub.angle, news.back.hub.angle);
            CHECK_EQ(orig.back.steer.speed, news.back.steer.speed);
            CHECK_EQ(orig.back.steer.angle, news.back.steer.angle);
            
            news = pos.switch_to(2);
            printf("Test case: 2 \nOriginal:");
            orig.Print();
            printf("New:");
            news.Print();

            CHECK_EQ(orig.left.hub.speed, news.back.hub.speed);
            CHECK_EQ(orig.left.hub.angle, news.back.hub.angle);
            CHECK_EQ(orig.left.steer.speed, news.back.steer.speed);
            CHECK_EQ(orig.left.steer.angle, news.back.steer.angle);

            CHECK_EQ(orig.right.hub.speed, news.left.hub.speed);
            CHECK_EQ(orig.right.hub.angle, news.left.hub.angle);
            CHECK_EQ(orig.right.steer.speed, news.left.steer.speed);
            CHECK_EQ(orig.right.steer.angle, news.left.steer.angle);

            CHECK_EQ(orig.back.hub.speed, news.right.hub.speed);
            CHECK_EQ(orig.back.hub.angle, news.right.hub.angle);
            CHECK_EQ(orig.back.steer.speed, news.right.steer.speed);
            CHECK_EQ(orig.back.steer.angle, news.right.steer.angle);

            news = pos.switch_to(0);
            printf("Test case: 0 \nOriginal:");
            orig.Print();
            printf("New:");
            news.Print();

            CHECK_EQ(orig.left.hub.speed, news.left.hub.speed);
            CHECK_EQ(orig.left.hub.angle, news.left.hub.angle);
            CHECK_EQ(orig.left.steer.speed, news.left.steer.speed);
            CHECK_EQ(orig.left.steer.angle, news.left.steer.angle);

            CHECK_EQ(orig.right.hub.speed, news.right.hub.speed);
            CHECK_EQ(orig.right.hub.angle, news.right.hub.angle);
            CHECK_EQ(orig.right.steer.speed, news.right.steer.speed);
            CHECK_EQ(orig.right.steer.angle, news.right.steer.angle);

            CHECK_EQ(orig.back.hub.speed, news.back.hub.speed);
            CHECK_EQ(orig.back.hub.angle, news.back.hub.angle);
            CHECK_EQ(orig.back.steer.speed, news.back.steer.speed);
            CHECK_EQ(orig.back.steer.angle, news.back.steer.angle);
            

        }
    }
}