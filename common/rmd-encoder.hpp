#pragma once

#include "devices/actuators/servo/rmd_x.hpp"

namespace sjsu::common
{
    class RmdEncoder {
    public:
        static float CalcEncoderPositions(sjsu::RmdX &motor)
        {
            //We shift right because the driver returns this value as a 16-bit number but the datasheet says its an 8 bit number
            int16_t raw_data = motor.RequestFeedbackFromMotor().GetFeedback().encoder_position;
            sjsu::LogInfo("raw_dat: %d", raw_data);
            int8_t raw_shifted_data = raw_data >> 8;
            sjsu::LogInfo("%raw shifted data: %d", raw_shifted_data);
            int8_t encoder_position_ = MapEncoderDataToDegrees(raw_shifted_data);
            sjsu::LogInfo("encoder position: %d", encoder_position_);
            return encoder_position_;
        }
    private:
        static int8_t MapEncoderDataToDegrees(int8_t encoder_data)
        {
            return (60 * encoder_data / 256);
        }

    };
}