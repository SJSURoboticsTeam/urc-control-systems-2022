#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc17xx/pwm.hpp"
#include "devices/actuators/servo/rmd_x.hpp"
#include "../library/devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "dto/arm-dto.hpp"
#include "../implementations/arm/mpu-router.hpp"
#include "../implementations/arm/arm-router.hpp"
#include "../implementations/mission-control-handler.hpp"





int main()
{
  sjsu::LogInfo("Starting the rover arm system...");
  sjsu::lpc40xx::Can & can = sjsu::lpc40xx::GetCan<2>();
  sjsu::StaticMemoryResource<1024> memory_resource;
  sjsu::CanNetwork can_network(can, &memory_resource);

  // RMD addresses 0x141 - 0x148 are available
  sjsu::RmdX rotunda_motor(can_network, 0x141);
  sjsu::RmdX shoulder_motor(can_network, 0x142);
  sjsu::RmdX elbow_motor(can_network, 0x143);
  sjsu::RmdX left_wrist_motor(can_network, 0x144);
  sjsu::RmdX right_wrist_motor(can_network, 0x145);

  rotunda_motor.settings.gear_ratio     = 8;
  shoulder_motor.settings.gear_ratio    = 8*65/16;  //gear ratio of motor times gear ratio of shoulder
  elbow_motor.settings.gear_ratio       = 8*5/2;    //gear ratio of motor times gear ratio of elbow
  left_wrist_motor.settings.gear_ratio  = 8;
  right_wrist_motor.settings.gear_ratio = 8;

  sjsu::arm::JointRouter arm(rotunda_motor, shoulder_motor, elbow_motor, left_wrist_motor, right_wrist_motor);
  sjsu::arm::RulesEngine rules_engine;
  sjsu::arm::MissionControlHandler mc_handler;

  sjsu::arm::arm_arguments arm_arguments;

  arm.Initialize();
  sjsu::LogInfo("Testing arm now");
  int i;
  while (true)
  {
    arm_arguments = mc_handler(arm_arguments);
    arm_arguments.joint_arguments = rules_engine.ValidateCommands(arm_arguments.joint_arguments)
    for(i = 0; i < 25; i++){
    arm.SetArmArguments({0, i, 0, 0, 0});
    sjsu::Delay(500ms);
    for(i; i > 0; i--){
    arm.SetArmArguments({0, i, 0, 0, 0});
    sjsu::Delay(500ms);
    }
    // sjsu::arm::arm_arguments arguments{5, 0, 20, 0, 0};
    // arm.SetArmArguments(arguments);
    // sjsu::Delay(3s);
    // sjsu::arm::arm_arguments arguments2{25, -10, 0, 0, 0};
    // arm.SetArmArguments(arguments);
    // sjsu::Delay(3s);
  }
  }
}