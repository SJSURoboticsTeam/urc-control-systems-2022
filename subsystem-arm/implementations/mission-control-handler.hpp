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
        char arm_mode, hand_mode;
        int actual_arguments = sscanf(
            response.c_str(), response_body_format, &mc_data_.heartbeat_count,
            &mc_data_.is_operational, &arm_mode, &hand_mode, &mc_data_.speed,
            &arm_mc_data_.arm_angles.rotunda, &arm_mc_data_.arm_angles.shoulder,
            &arm_mc_data_.arm_angles.elbow, &hand_mc_data_.wrist_data.roll,
            &hand_mc_data_.wrist_data.pitch,
            &hand_mc_data_.finger_angles.pinky_angle,
            &hand_mc_data_.finger_angles.ring_angle,
            &hand_mc_data_.finger_angles.middle_angle,
            &hand_mc_data_.finger_angles.pointer_angle,
            &hand_mc_data_.finger_angles.thumb_angle);
    
        arm_mc_data_.arm_mode   = Arm::MissionControlData::ArmModes{ arm_mode };
        hand_mc_data_.hand_mode = Hand::MissionControlData::HandModes{ hand_mode };
        if (actual_arguments != kExpectedArguments)
        {
          sjsu::LogError("Arguments# %d != expected# %d!", actual_arguments,
                         kExpectedArguments);
          throw ParseError{};
        }
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