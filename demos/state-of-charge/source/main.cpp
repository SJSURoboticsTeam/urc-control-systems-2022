#include "../../common/state_of_charge.hpp"
#include "utility/log.hpp"
#include "peripherals/lpc17xx/i2c.hpp"
#include "peripherals/lpc40xx/gpio.hpp"
#include "peripherals/hardware_counter.hpp"

sjsu::InterruptCallback callback;
uint8_t address = 0b0110110;
sjsu::lpc40xx::I2c &i2c = sjsu::lpc40xx::GetI2c<2>();
sjsu::lpc40xx::Gpio &alert_pin = sjsu::lpc40xx::GetGpio<0, 6>();
sjsu::Max17043 module(i2c, alert_pin, callback, address);

int main()
{
    sjsu::LogInfo("Connecting to Max17043...");
    sjsu::common::StateOfCharge battery(module);
    battery.Initialize();
    while (1)
    {
        sjsu::Delay(2000ms);
        sjsu::LogInfo("Battery Percentage: %f%% | Remaining Current Voltage: %fV", battery.BatteryPercentage(), battery.StateOfCharge());
    }

    return 0;
}