#include "../implementation/cd74hc4067.hpp"

// Signal ports and pins for GPIO digital pins to control the mux.
// order for each macros is channel, port
#define SIGNAL_0 2, 1
#define SIGNAL_1 2, 4
#define SIGNAL_2 2, 6
#define SIGNAL_3 2, 8
#define ADC_CHANNEL 4
// 1, 30 ADC output used for 5 pots.



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
        input_deg = input_deg / 360;
    
    return input_deg - new_zero;
}

int main()
{
    sjsu::lpc40xx::Adc& adc4 = sjsu::lpc40xx::GetAdc<ADC_CHANNEL>(); 
    auto& s0 = sjsu::lpc40xx::GetGpio<SIGNAL_0>();
    auto& s1 = sjsu::lpc40xx::GetGpio<SIGNAL_1>();
    auto& s2 = sjsu::lpc40xx::GetGpio<SIGNAL_2>();
    auto& s3 = sjsu::lpc40xx::GetGpio<SIGNAL_3>();

    auto digital_multiplexer = Cd74hc4067(adc4, s0, s1, s2, s3);
    sjsu::LogInfo("Signal pins configured");
    sjsu::LogInfo("ADC initialized.");
    
    // demo code
    // TODO: move to its own file.
    while(true)
    {
        const size_t N = 3;
        std::array<unsigned int, N> channels = {0, 1, 2};
        std::array<float, N> output = digital_multiplexer.ReadAll<N>(channels);
        for (int i = 0; i < N; i++)
        {
            float degree = DegreePhaseShift(VoltageToTrueDegree(output[i], 3.3, 180), 90);
            sjsu::LogInfo("Channel %i: Degree: %f", channels[i], degree);
           // sjsu::LogInfo("Channel %i: Voltage: %f", channels[i], output[i]);
        }
    }

    // Control loop for mimic arm controller
    // Rotunda (channel 0) and wrist rotate (channel 4)
    while (true)
    {
        // read voltages from pots
        std::array<float, 5> output_voltages = digital_multiplexer.ReadAll<5>({0, 1, 2, 3, 4});
        std::array<float, 5> degree_conversion = {360, 90, 90, 90, 360};
        std::array<float, 5> results = {};
        for (int i = 0; i < 5; i++)
        {
            float true_degree = VoltageToTrueDegree(output_voltages[i], 3.3, 360);
            results[i] = DegreePhaseShift(true_degree, degree_conversion[i]);
        }

        // TODO: POST to mission control various degrees
    }

    return 0;

}