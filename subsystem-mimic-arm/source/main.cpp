#include "../implementation/cd74hc4067.hpp"

// Signal ports and pins for GPIO digital pins to control the mux.
// order for each macros is channel, port
#define SIGNAL_0 2, 1
#define SIGNAL_1 2, 4
#define SIGNAL_2 2, 6
#define SIGNAL_3 2, 8
#define ADC_CHANNEL 4
// 1, 30 ADC output used for 5 pots.



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
        std::array<unsigned int, 5> channels = {0, 1, 2, 3, 4};
        std::array<float, 5> output = digital_multiplexer.ReadAll<5>(channels);
        for (int i = 0; i < 5; i++)
            sjsu::LogInfo("Channel %i: Voltage: %f", channels[i], output[i]);
    }

    return 0;

}