#pragma once

#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::common
{
    class RmdEncoder {
    public:
        static float CalcEncoderPositions(sjsu::RmdX &motor)
        {
            //We shift right because the driver returns this value as a 16-bit number but the datasheet says its an 8 bit number
            return MapEncoderDataToDegrees(static_cast<float>(motor.RequestFeedbackFromMotor().GetFeedback().encoder_position >> 8));
        }
    private:
        static float MapEncoderDataToDegrees(float encoder_data)
        {
            // sjsu::LogInfo("%d", encoder_data);
            float temp = (60.0f * encoder_data / 256.0f);
            // sjsu::LogInfo("%d", temp);
            return temp;
        }

    };
}