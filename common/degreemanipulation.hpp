#pragma once

#include "utility/math/map.hpp"
#include <stdexcept>

namespace sjsu::common {
    
    /// @brief Converts raw voltage from a potentiometer to the true degree given an input voltage and a ratio between volts and degrees.
    /// 3.3V is considered 0 degrees
    /// @param voltage The input voltage
    /// @param volt_to_deg_ratio The ratio of voltage to one degree (how much voltage is changed when the pot moves one degree)
    /// @return The degree of the potentiometer.
    float VoltageToTrueDegree(float voltage, float max_voltage, float max_degree)
    {
        return sjsu::Map(voltage, 0, max_voltage, 0, max_degree);
    }

    /// @brief Changes where zero degrees is. Processes a true degree to be in relation to the offset degree. 
    /// Example: If the new zero in true degrees is 90 degrees, and you pass in an input of 45 degrees, you're result will be -45 degrees.
    /// @param input_deg The angle in true degrees you wish to map.
    /// @param new_zero The new location on the unit circle where zero should start.
    /// @return The phase shifted angle.
    float DegreePhaseShift(float input_deg, float new_zero)
    {
        if (new_zero < 0 || new_zero > 360)
            throw std::invalid_argument("This function only considers the unit circle. Please set new_zero to the position on the unit circle it will be.");
        
        while (input_deg > 360 || input_deg < -360)
        {
            // take modulus of a float without losing data
            input_deg = input_deg / 360;
            input_deg = (input_deg - static_cast<int>(input_deg)) * 360;
        }
        
        return input_deg - new_zero;
    }

}