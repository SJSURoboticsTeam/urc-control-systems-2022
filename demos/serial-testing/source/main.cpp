#include <cstdint>

#include "utility/log.hpp"
#include "peripherals/lpc40xx/uart.hpp"
#include "peripherals/lpc40xx/gpio.hpp"

#include "serial.hpp"
#include "arm-dto.hpp"
#include "drive-dto.hpp"

sjsu::arm::arm_arguments arm_args;
sjsu::drive::drive_commands drive_args;

void ArmCommandsParser(std::string input)
{
    if (input != "")
    {
        sscanf(input.c_str(), sjsu::arm::kResponseBodyFormat,
               &arm_args.joint_args.heartbeat_count, &arm_args.joint_args.is_operational, &arm_args.joint_args.speed,
               &arm_args.joint_args.mode, &arm_args.joint_args.rotunda_angle, &arm_args.joint_args.shoulder_angle,
               &arm_args.joint_args.elbow_angle, &arm_args.joint_args.wrist_pitch_angle, &arm_args.joint_args.wrist_yaw_angle,
               &arm_args.hand_args.mode, &arm_args.hand_args.pinky_angle, &arm_args.hand_args.ring_angle,
               &arm_args.hand_args.middle_angle, &arm_args.hand_args.index_angle, &arm_args.hand_args.thumb_angle);
    }
}

void DriveCommandsParser(std::string input)
{
    if (input != "")
    {
        sscanf(input.c_str(), sjsu::drive::kResponseBodyFormat,
               &drive_args.heartbeat_count, &drive_args.is_operational, &drive_args.wheel_orientation,
               &drive_args.mode, &drive_args.speed, &drive_args.angle);
    }
}

int main()
{
    sjsu::LogInfo("Serial Testing Starting...");
    sjsu::common::Serial serial(sjsu::lpc40xx::GetUart<0>());

    while (true)
    {
        std::string response = serial.GetCommands();
        if (response != "")
        {
            printf("Received:\n%s\n", response.c_str());
            printf("Parsed:\n");
            ArmCommandsParser(response);
            arm_args.Print();
            // DriveCommandsParser(response);
            // drive_args.Print();
        }
    }

    return 0;
}