#include "utility/log.hpp"
#include "peripherals/lpc40xx/i2c.hpp"
#include "peripherals/lpc40xx/can.hpp"
#include "peripherals/lpc17xx/pwm.hpp"
#include "devices/actuators/servo/rmd_x.hpp"
#include "../library/devices/sensors/movement/accelerometer/mpu6050.hpp"
#include "dto/arm-dto.hpp"
#include "../implementations/joints/mpu-router.hpp"
#include "../implementations/joints/joint-router.hpp"
#include "../implementations/mission-control-handler.hpp"
#include "../common/serial.hpp"
#include "peripherals/lpc40xx/uart.hpp"

using namespace sjsu::arm;

int main()
{
  sjsu::LogInfo("Starting the rover arm system...");
  sjsu::lpc40xx::Can &can = sjsu::lpc40xx::GetCan<2>();
  sjsu::StaticMemoryResource<1024> memory_resource;
  sjsu::CanNetwork can_network(can, &memory_resource);

  // RMD addresses 0x141 - 0x148 are available
  sjsu::RmdX rotunda_motor(can_network, 0x141);
  sjsu::RmdX shoulder_motor(can_network, 0x142);
  sjsu::RmdX elbow_motor(can_network, 0x143);
  sjsu::RmdX left_wrist_motor(can_network, 0x144);
  sjsu::RmdX right_wrist_motor(can_network, 0x145);

  rotunda_motor.settings.gear_ratio = 8;
  shoulder_motor.settings.gear_ratio = 8 * 65 / 16; // gear ratio of motor times gear ratio of shoulder
  elbow_motor.settings.gear_ratio = 8 * 5 / 2;      // gear ratio of motor times gear ratio of elbow
  left_wrist_motor.settings.gear_ratio = 8;
  right_wrist_motor.settings.gear_ratio = 8;

  sjsu::arm::JointRouter arm(rotunda_motor, shoulder_motor, elbow_motor, left_wrist_motor, right_wrist_motor);
  sjsu::arm::MissionControlHandler mc_handler;

  sjsu::arm::arm_arguments arm_arguments;
  sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());

  arm.Initialize();
  sjsu::LogInfo("Testing arm now");
  int i;
  arm.HomeArm();
  while (true)
  {
    std::string commands = serial.GetSerialCommands();
    // remove_if(commands.begin(), commands.end(), isspace);
    if (commands != "")
    {
      sjsu::LogInfo("%s", commands.c_str());
      // printf("%s", commands.c_str());
    }

    // printf("%s", commands.c_str());
    //  printf(kJointBodyFormat, 0,1,2,3,4,5,6,7,'8',1,2,3,4,5,'6');
  }
}