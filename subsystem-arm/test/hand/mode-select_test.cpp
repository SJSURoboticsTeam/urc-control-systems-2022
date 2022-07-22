#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "../implementations/hand/mode-select.hpp"
#include "../dto/arm-dto.hpp"
#include "../implementations/pca9685.hpp"


namespace sjsu::arm
{
    TEST_CASE("Hand Mode Select Testing")
    {
        //Stay in the default mode be rover powers on
        //Shouldn't change modes unless told to
        //Change to the correct mode it's given from mission control
    }
}