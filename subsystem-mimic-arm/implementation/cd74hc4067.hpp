#pragma once
#include "peripherals/lpc40xx/adc.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
#include "utility/log.hpp"
#include "utility/math/map.hpp"
#include "utility/time/time.hpp"
#include <array>

/// @brief An implementation for the CD74HC4067 multiplexer. This multiplexer has 16 channels and 4 signal pins to switch the channels in binary.
class Cd74hc4067
{
public:
    /// @brief Constructor Sets all digital signal pins to be outputs and sets them to LOW.
    /// @param adc A dev2 ADC instance pin. It can be initalized or not.
    /// @param s0 A dev2 digital GPIO pin. It can be initalized or not.
    /// @param s1 A dev2 digital GPIO pin. It can be initalized or not.
    /// @param s2 A dev2 digital GPIO pin. It can be initalized or not.
    /// @param s3 A dev2 digital GPIO pin. It can be initalized or not.
    Cd74hc4067(
        sjsu::lpc40xx::Adc& adc,
        sjsu::lpc40xx::Gpio& s0,
        sjsu::lpc40xx::Gpio& s1,
        sjsu::lpc40xx::Gpio& s2,
        sjsu::lpc40xx::Gpio& s3): adc_{adc}, s0_{s0}, s1_{s1}, s2_{s2}, s3_{s3} {
            // Initialize if not already, unsure if you 
            adc_.Initialize();
            s0_.Initialize();
            s1_.Initialize();
            s2_.Initialize();
            s3_.Initialize();

            // set our digital signalling pins to output.
            s0_.SetAsOutput();
            s1_.SetAsOutput();
            s2_.SetAsOutput();
            s3_.SetAsOutput();

            // pins default as high, set to low.
            s0_.SetLow();
            s1_.SetLow();
            s2_.SetLow();
            s3_.SetLow();
        }
    
    /// @brief Switches between multiplexer channels. Not intended to be called directly but to be used in a reading function.
    /// @param number The channel to switch to.
    void SwapChannels(unsigned int number)
    {
        s0_.Set(sjsu::Gpio::State(bool(number & (1 << 0))));
        s1_.Set(sjsu::Gpio::State(bool(number & (1 << 1))));
        s2_.Set(sjsu::Gpio::State(bool(number & (1 << 2))));
        s3_.Set(sjsu::Gpio::State(bool(number & (1 << 3))));
    }
    
    /// @brief Reads a list of N channels up to 16, function takes 10 readings and then averages them.
    /// @tparam N The number of channels you wish to read. Cannot be higher than 16.
    /// @param channel_list An std::array of size N of the channels to read from. (Channels must not be lower than 0 or higher than 16)
    /// @return An N sized std::array of all the voltages for each channel in channel_list. The voltages in the same order as the channels given.
    template <unsigned int N>
    std::array<float, N> ReadAll(std::array<unsigned int, N> channel_list)
    {
        if (N > 16)
        {   
            auto e_msg = "Number given larger than 16, only 16 pins on the multiplexer.";
            sjsu::LogError("%s", e_msg);
            throw std::invalid_argument(e_msg);
        }

        float average = 0;
        std::array<float, N> results;
        results.fill(0);
        for (unsigned int i = 0; i < N; i++)
        {
            // switch channel
            average = 0;
            SwapChannels(channel_list[i]);
            sjsu::Delay(5ms);
            for (int j = 0; j < 10; j++)
            {
                auto digital_value = adc_.Read(); // read input
                float voltage = sjsu::Map(digital_value, 0, adc_.GetMaximumValue(), 0.0f, 3.3f); // bind our voltage between 0 and 3.3 volts
                average += voltage;
            }
            average = average / 10;
            results[i] = average;
        }
        return results;
    }
    
    /// @brief Reads a single multiplexer channel.
    /// @param channel The channel to be read on the multiplexer. (Channels must not be lower than 0 or higher than 16).
    /// @return The voltage of the channel selected.
    float ReadOne(unsigned int channel)
    {
        std::array<unsigned int, 1> c_list = {channel}; 
        return ReadAll<1>(c_list)[0];
    }

private:
    sjsu::lpc40xx::Adc& adc_;
    sjsu::lpc40xx::Gpio& s0_;
    sjsu::lpc40xx::Gpio& s1_;
    sjsu::lpc40xx::Gpio& s2_;
    sjsu::lpc40xx::Gpio& s3_;

};