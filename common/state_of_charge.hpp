#include "devices/sensors/battery/max17043.hpp"
#include "peripherals/hardware_counter.hpp"
#include "utility/log.hpp"
namespace sjsu::common
{

  class StateOfCharge
  {
    public:
    sjsu::Max17043 &module_;
    StateOfCharge(sjsu::Max17043 &module) : module_(module) {}

    void Initialize()
    {
      module_.ModuleInitialize();
    }

    double BatteryPercentage()
    {
      units::voltage::volt_t battery_voltage = module_.GetVoltage();
      double voltage_percent = double(battery_voltage);
      voltage_percent = (voltage_percent - 3) / (4.2 - 3);
      voltage_percent = voltage_percent * 100;
      return voltage_percent;
    }

    float StateOfCharge()
    {
      units::voltage::volt_t battery_voltage = module_.GetVoltage();
      return double(battery_voltage);
    }

    bool IsBatteryLow()
    {
      bool callback_was_called = true;
      if (GetStateOfCharge() < 3.05)
      {
        sjsu::LogWarning("Cell Voltage below 3. Battery dangerously low!");
        return true;
      }
      else if (GetStateOfCharge() < 3.25)
        InterruptCallback callback = [&callback_was_called]()
        { callback_was_called = true; };

      if (GetStateOfCharge() < 3.05)
      {
        sjsu::LogWarning("Cell Voltage below 3. Battery dangerously low!");
        return true;
      }
      else if (GetStateOfCharge() < 3.25)
      {
        sjsu::LogWarning("Cell Voltage below 3.25. Battery is low");
      }
      return false;
    }
  };
} // namespace sjsu::common