#include "devices/sensors/battery/max17043.hpp"
#include "peripherals/hardware_counter.hpp"
#include "utility/log.hpp"
namespace sjsu::common
{

  class StateOfCharge
  {
  public:
    StateOfCharge(sjsu::Max17043 &module) : module_(module) {}

    void Initialize()
    {
      module_.ModuleInitialize();
    }

    float BatteryPercentage()
    {
      units::voltage::volt_t battery_voltage = module_.GetVoltage();
      float voltage_percent = static_cast<float>(battery_voltage);
      voltage_percent = (voltage_percent - kLowBatteryVoltage) / (kFullBatteryVoltage - kLowBatteryVoltage);
      voltage_percent = voltage_percent * 100;
      return voltage_percent;
    }

    float GetStateOfCharge()
    {
      return static_cast<float>(module_.GetVoltage());
    }

    bool IsBatteryLow()
    {}

  private:
    const float kFullBatteryVoltage = 4.2;
    const float kLowBatteryVoltage = 3.0;
    sjsu::Max17043 &module_;
  };
} // namespace sjsu::common
