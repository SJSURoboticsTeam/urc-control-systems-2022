#pragma once
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{

    const char response_body_format[] = "";

    class MissionControlHandler
    {
    public:
        arm_commands ParseMissionControlData(std::string &response)
        {
              int actual_arguments = sscanf(
                response.c_str(), response_body_format,
                &commands.rotunda_angle, &commands.shoulder_angle, &commands.elbow_angle,
                &commands.wrist_pitch_angle, &commands.wrist_yaw_angle, &commands.mode);

            return commands;
        }
        std::string CreateGETRequestParameterWithRoverStatus()
        {
            char request_parameter[300];
            snprintf(request_parameter, 300,
                 "?heartbeat_count=%d&is_operational=%d&arm_mode=%c&hand_mode=%c&"
                 "arm_speed=%d&battery=%d&rotunda_angle=%d&shoulder_angle=%d&elbow_"
                 "angle=%d&wrist_roll=%d&wrist_pitch=%d&pinky_angle=%d&ring_angle=%"
                 "d&middle_angle=%d&pointer_angle=%d&thumb_angle=%d",
                 GetHeartbeatCount(), mc_data_.is_operational,
                 static_cast<char>(arm_mc_data_.arm_mode),
                 static_cast<char>(hand_mc_data_.hand_mode), int(mc_data_.speed),
                 static_cast<int>(st.GetStateOfCharge()), arm_.GetRotundaPosition(),
                 arm_.GetShoulderPosition(), arm_.GetElbowPosition(),
                 hand_.GetWristRoll(), hand_.GetWristPitch(),
                 hand_.GetPinkyPosition(), hand_.GetRingPosition(),
                 hand_.GetMiddlePosition(), hand_.GetPointerPosition(),
                 hand_.GetThumbPosition());
            return request_parameter;
        }

    private:
        arm_commands commands;
        char request_parameter[300];
    };
}