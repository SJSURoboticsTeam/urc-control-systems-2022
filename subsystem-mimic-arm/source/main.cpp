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
    
    while(true)
    {
        const size_t N = 3;
        std::array<unsigned int, N> channels = {0, 1, 2};
        std::array<float, N> output = digital_multiplexer.ReadAll<N>(channels);
        for (int i = 0; i < N; i++)
        {
            sjsu::LogInfo("Channel %i: Degree: %f", channels[i], VoltageToTrueDegree(output[i], 3.3, 180));
           // sjsu::LogInfo("Channel %i: Voltage: %f", channels[i], output[i]);
        }
    }

    return 0;

}