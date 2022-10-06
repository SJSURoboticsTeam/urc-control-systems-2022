#pragma once

#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::common
{
    class RmdEncoder {
    public:
        // if home is true, this encoder will return where it is at within its 60 degree segment, 
        // if false, it will return where it is with respect to where it set it's 0 to
         
        static float CalcEncoderPositions(sjsu::RmdX &motor, bool home)
        {
            //We shift right because the driver returns this value as a 16-bit number but the datasheet says its an 8 bit number
            return MapEncoderDataToDegrees(motor.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8, home);
        }
    private:
        static float MapEncoderDataToDegrees(float encoder_data, bool home)
        {
            return (home ? (60.0 * encoder_data / 256.0) : (360.0 * encoder_data / 256.0));
        }
    };
}