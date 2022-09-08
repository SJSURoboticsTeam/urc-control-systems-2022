#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc17xx/pwm.hpp"
#include "devices/actuators/servo/rmd_x.hpp"
#include "../library/devices/sensors/movement/accelerometer/mpu6050.hpp"

#include "../implementations/joints/mpu-router.hpp"
#include "../implementations/joints/joint-router.hpp"
#include "../implementations/hand/hand-router.hpp"
#include "../implementations/mission-control-handler.hpp"
#include "../implementations/joints/rules-engine.hpp"
#include "../implementations/hand/rules-engine.hpp"
#include "../common/serial.hpp"
//#include "../common/esp.hpp"
#include "dto/arm-dto.hpp"

using namespace sjsu::arm;

int main()
{
  // sjsu::common::Esp esp;
  sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
  sjsu::Pca9685 pca9685(sjsu::lpc40xx::GetI2c<2>(), 0x40);
  sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
  sjsu::StaticMemoryResource<1024> memory_resource;
  sjsu::CanNetwork can_network(can, &memory_resource);

  // RMD addresses 0x141 - 0x148 are available
  sjsu::RmdX rotunda_motor(can_network, 0x141);
  sjsu::RmdX shoulder_motor(can_network, 0x142);
  sjsu::RmdX elbow_motor(can_network, 0x143);
  sjsu::RmdX left_wrist_motor(can_network, 0x144);
  sjsu::RmdX right_wrist_motor(can_network, 0x145);

  // TODO: Verify gear ratios
  rotunda_motor.settings.gear_ratio = 8;
  shoulder_motor.settings.gear_ratio = 8 * 65 / 16;
  elbow_motor.settings.gear_ratio = 8 * 5 / 2;
  left_wrist_motor.settings.gear_ratio = 8;
  right_wrist_motor.settings.gear_ratio = 8;

  JointRouter joint_router(rotunda_motor, shoulder_motor, elbow_motor, left_wrist_motor, right_wrist_motor);
  HandRouter hand_router(pca9685);
  // TODO: MpuRouter mpu_router();
  MissionControlHandler mission_control;
  JointsRulesEngine joints_rules_engine;
  HandRulesEngine hand_rules_engine;
  arm_arguments arguments;

  joint_router.Initialize();
  joint_router.HomeArm();

  sjsu::Delay(1s);
  sjsu::LogInfo("Starting the rover arm system...");

  while (1)
  {
    std::string response = serial.GetCommands();
    if (response != "")
    {
      printf("Received:\n%s\n", response.c_str());
      printf("Parsed:\n");
      arguments = mission_control.ParseMissionControlData(response);
      arguments = joints_rules_engine.ValidateCommands(arguments);
      // arguments = hand_rules_engine.ValidateCommands(arguments); // TODO: Needs rework
      arguments.Print();
    }
    joint_router.SetArmArguments(arguments);
  }
}