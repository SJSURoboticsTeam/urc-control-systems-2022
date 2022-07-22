#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/hand/hand-router.hpp"
#include "../dto/arm-dto.hpp"
#include "../implementations/pca9685.hpp"
#include "utility/math/units.hpp"

namespace sjsu::arm
{
    TEST_CASE("Hand Router Testing")
    {

        // Check if AngleToPulse() is correctly converting angles to pulse
        // SECTION("2.1 Check if AngleToPulse() is correctly converting angles to pulse")
        // {
        //     HandRouter hand_router_{};
        //     std::chrono::microseconds original_pulse = std::chrono::microseconds(1024);
        //     std::chrono::microseconds args = hand_router_.AngleToPulseWidth(90);
        //     CHECK_EQ(args, original_pulse);
        // }
    }
}