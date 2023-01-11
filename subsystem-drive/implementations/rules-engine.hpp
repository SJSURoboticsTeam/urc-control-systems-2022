#pragma once

#include "../dto/drive-dto.hpp"
#include "../common/heartbeat.hpp"
#include "../implementations/mission-control-handler.hpp"

namespace sjsu::drive
{
    class RulesEngine
    {
    public:
        static constexpr int kMaxSpeed = 100;
        static constexpr int kMaxAngle = 12;

        drive_commands ValidateCommands(drive_commands commands)
        {
            int count =0;
            if (commands.mode == 'D')
            {
                // sjsu::LogInfo("Specified angle is too large... clamping angle");
                commands.angle = std::clamp(commands.angle, -kMaxAngle, kMaxAngle);
            }
            for(int i=0; i<4;i++){//check four times if the heartbeat from mc and rover are the same
                if(heartbeat_.IsSyncedWithMissionControl(mc_.commands_.heartbeat_count)){
                    count++;
                }
            }
            if(count==4){
                sjsu::LogInfo("Heartbeat is in sync... setting the speed");
                return commands;
            }else{
                sjsu::LogInfo("Heartbeat is out of sync... setting speed to 0");
                commands.speed = 0;
                return commands;
            }
            // if(!heartbeat_.IsSyncedWithMissionControl(commands.heartbeat_count))
            // {
            //     //sjsu::LogInfo("Heartbeat is out of sync... setting speed to 0");
            //     commands.speed = 0;
            //     return commands;
            // }
            if (!commands.is_operational)
            {
                // sjsu::LogInfo("System is not operational... setting speed to 0");
                commands.speed = 0;
                return commands;
            }
            if (commands.speed > kMaxSpeed || commands.speed < -kMaxSpeed)
            {
                // sjsu::LogInfo("Specified speed is too fast... clamping speed");
                commands.speed = std::clamp(commands.speed, -kMaxSpeed, kMaxSpeed);
            }

            heartbeat_.IncrementHeartbeatCount();
            return commands;
        }

    private:
        sjsu::common::Heartbeat heartbeat_;
        sjsu::drive::MissionControlHandler mc_;
    };
}