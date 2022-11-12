#include "peripherals/lpc40xx/adc.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
#include "utility/log.hpp"
#include "utility/math/map.hpp"
#include "utility/time/time.hpp"

// Signal ports and pins for GPIO digital pins to control the mux.
// order for each macros is channel, port
#define SIGNAL_0 2, 1
#define SIGNAL_1 2, 4
#define SIGNAL_2 2, 6
#define SIGNAL_3 2, 8


// parse number into binary and set pins accordingly
void SwapChannels(unsigned int number, sjsu::lpc40xx::Gpio& s0, sjsu::lpc40xx::Gpio& s1, sjsu::lpc40xx::Gpio& s2, sjsu::lpc40xx::Gpio& s3)
{
    using namespace sjsu;

    s0.Set(Gpio::State(bool(number & (1 << 0))));
    s1.Set(Gpio::State(bool(number & (1 << 1))));
    s2.Set(Gpio::State(bool(number & (1 << 2))));
    s3.Set(Gpio::State(bool(number & (1 << 3))));
}

int main()
{   // TODO: refactor into separate function
    sjsu::Adc& adc4 = sjsu::lpc40xx::GetAdc<4>(); // 1, 30 ADC output used for 5 pots.
    auto& s0 = sjsu::lpc40xx::GetGpio<SIGNAL_0>();
    auto& s1 = sjsu::lpc40xx::GetGpio<SIGNAL_1>();
    auto& s2 = sjsu::lpc40xx::GetGpio<SIGNAL_2>();
    auto& s3 = sjsu::lpc40xx::GetGpio<SIGNAL_3>();
    s0.Initialize();
    s1.Initialize();
    s2.Initialize();
    s3.Initialize();

    s0.SetAsOutput();
    s1.SetAsOutput();
    s2.SetAsOutput();
    s3.SetAsOutput();

    // pins default as high, set to low.
    s0.SetLow();
    s1.SetLow();
    s2.SetLow();
    s3.SetLow();
    sjsu::LogInfo("Signal pins configured");
    adc4.Initialize();
    sjsu::LogInfo("ADC initialized.");

    //return 0;

    while(true)
    {
        sjsu::LogInfo("New loop cycle.");
        unsigned int channels[] = {0b0000, 0b0001, 0b0010, 0b0011, 0b0100};
        float results[5] = {0,0,0,0,0};
        for (int i = 0; i < 5; i++)
        {
            // switch channel
            auto channel = channels[i];
            sjsu::LogInfo("Switching to channel: %i", channel);
            SwapChannels(channel, s0, s1, s2, s3);
            sjsu::Delay(5ms);
            auto digital_value = adc4.Read(); // read input
            float voltage = sjsu::Map(digital_value, 0, adc4.GetMaximumValue(), 0.0f, 3.3f); // bind our voltage between 0 and 3.3 volts
            results[i] = voltage;
            sjsu::LogInfo("Channel %i: Voltage is: %f\n", i, results[i]);
            sjsu::Delay(5ms);
        }
       
        sjsu::LogInfo("\n");
    }

    return 0;

}