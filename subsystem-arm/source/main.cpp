#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc17xx/pwm.hpp"
#include "devices/actuators/servo/rmd_x.hpp"
#include "devices/sensors/movement/accelerometer/mpu6050.hpp"

#include "../implementations/routers/joint-router.hpp"
#include "../implementations/routers/hand-router.hpp"
#include "../implementations/routers/mpu-router.hpp"
#include "../implementations/routers/tca9458a-router.hpp"

#include "../implementations/mission-control-handler.hpp"
#include "../implementations/rules-engine.hpp"
#include "../implementations/mode-select.hpp"
#include "../implementations/pca9685.hpp"
#include "../common/serial.hpp"
//#include "../common/esp.hpp"
#include "dto/arm-dto.hpp"

using namespace sjsu::arm;

int main()
{
  // sjsu::common::Esp esp;
  sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());
  sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<1>();
  sjsu::StaticMemoryResource<1024> memory_resource;
  sjsu::CanNetwork can_network(can, &memory_resource);

  // RMD addresses 0x141 - 0x148 are available
  sjsu::RmdX rotunda_motor(can_network, 0x141);
  sjsu::RmdX shoulder_motor(can_network, 0x142);
  sjsu::RmdX elbow_motor(can_network, 0x143);
  sjsu::RmdX left_wrist_motor(can_network, 0x144);
  sjsu::RmdX right_wrist_motor(can_network, 0x145);
  sjsu::Pca9685 pca9685(sjsu::lpc40xx::GetI2c<2>(), 0x40);

  // TODO: Verify gear ratios
  rotunda_motor.settings.gear_ratio = 8;
  shoulder_motor.settings.gear_ratio = 8 * 65 / 16;
  elbow_motor.settings.gear_ratio = 8 * 5 / 2;
  left_wrist_motor.settings.gear_ratio = 8;
  right_wrist_motor.settings.gear_ratio = 8;

  JointRouter joint_router(rotunda_motor, shoulder_motor, elbow_motor, left_wrist_motor, right_wrist_motor);
  HandRouter hand_router(pca9685);
  MissionControlHandler mission_control;
  RulesEngine rules_engine;
  // TODO: Fix hand from crashing program when pca9685 is not connected!
  arm_arguments arguments;
  mc_commands commands;

  joint_router.Initialize();
  // joint_router.HomeArm();
  // hand_router.Initialize();

  sjsu::LogInfo("Starting control loop...");
  sjsu::Delay(1s);

  while (1)
  {
    std::string response = serial.GetCommands();
    if (response.find('{') != std::string::npos && response.find('}') != std::string::npos)
    {
      // TODO: Make this work w Joystick Serial
      printf("Received:\n%s\n", response.c_str());
      commands = mission_control.ParseMissionControlData(response);
      commands = rules_engine.ValidateCommands(commands);
    }
    arguments = ModeSelect::SelectMode(commands, arguments);
    commands.Print();
    if(commands.mode == 'J') {
      arguments.joint_args = joint_router.SetJointArguments(arguments.joint_args);
    }
    else {
      arguments.hand_args = hand_router.SetHandArguments(arguments.hand_args, commands.mode);
    }
  }
}