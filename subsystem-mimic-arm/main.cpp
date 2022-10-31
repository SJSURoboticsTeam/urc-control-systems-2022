

#include "peripherals/lpc40xx/adc.hpp"
#include "utility/log.hpp"
#include "utility/math/map.hpp"
#include "utility/time/time.hpp"

int main()
{
    sjsu::Adc & adc4 = sjsu::lpc40xx::GetAdc<4>();
    adc4.Initialize();
    sjsu::LogInfo("ADC initialized.");

    while(true)
    {
        auto digital_value = adc4.Read(); // read input
        float voltage = sjsu::Map(digital_value, 0, adc4.GetMaximumValue(), 0.0f, 3.3f); // bind our voltage between 0 and 3.3 volts
        sjsu::LogInfo("Potentiometer is reading: %.5f V (%04lu)", static_cast<double>(voltage), digital_value);
        sjsu::Delay(10ms);

    }

    return 0;
}