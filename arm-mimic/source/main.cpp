#include "../implementation/cd74hc4067.hpp"
#include "../../common/degreemanipulation.hpp"

// Signal ports and pins for GPIO digital pins to control the mux.
// order for each macros is channel, port
#define SIGNAL_0 2, 1
#define SIGNAL_1 2, 4
#define SIGNAL_2 2, 6
#define SIGNAL_3 2, 8
#define ADC_CHANNEL 4
// 1, 30 ADC output used for 5 pots.

/// TODO: Update to use proper http POST requests
template <unsigned int N>
void send_data_mc(std::array<float, N> raw_data)
{
    // Structure of json file
    /* 
    { 
        HB: 0,
        IO: 1,
        M: 'M',
        Angles: [$ROTUNDA, $SHOULDER, $ELBOW, $WRIST_PITCH, $WRIST_ROLL, $END_EFFECTOR]
    }
    */
    std::string json_str = "{\"HB\":\"0\",\"IO\":\"1\",\"M\":\"M\",\"CMD\":[";
    for (unsigned int i = 0; i < N; i++)
    {
        if (i != N - 1)
            json_str.append(std::to_string(raw_data[i]) + ",");
        else
            json_str.append(std::to_string(raw_data[i]));
    }
    
    json_str.append("]}");
    printf("%s", json_str.c_str()); // print to serial
}

int main()
{
    auto& adc4 = sjsu::lpc40xx::GetAdc<ADC_CHANNEL>(); 
    auto& s0 = sjsu::lpc40xx::GetGpio<SIGNAL_0>();
    auto& s1 = sjsu::lpc40xx::GetGpio<SIGNAL_1>();
    auto& s2 = sjsu::lpc40xx::GetGpio<SIGNAL_2>();
    auto& s3 = sjsu::lpc40xx::GetGpio<SIGNAL_3>();

    auto digital_multiplexer = Cd74hc4067(adc4, s0, s1, s2, s3);

    while (true)
    {
        // Pot order: ROTUNDA, SHOULDER, ELBOW, WRIST_PITCH, WRIST_ROLL, END_EFFECTOR
        const size_t N = 6;
        std::array<unsigned int, N> channels = {0, 1, 2, 3, 4, 5};
        // read voltages from pots
        std::array<float, N> output_voltages = digital_multiplexer.ReadAll<N>(channels);
        /// TODO: double check scaling.
        std::array<float, N> degree_conversion = {360, 90, 90, 90, 360, 360}; 
        std::array<float, N> results = {};
        /// Convert voltages to degree at specified phase.
        for (size_t i = 0; i < N; i++)
        {
            float true_degree = sjsu::common::VoltageToTrueDegree(output_voltages[i], 3.3f, 360);
            results[i] = sjsu::common::DegreePhaseShift(true_degree, degree_conversion[i]);
        }
        send_data_mc<N>(results);

    }
    return 0;
}