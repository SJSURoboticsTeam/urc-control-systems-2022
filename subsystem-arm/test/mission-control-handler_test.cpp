#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "implementations/mission-control-handler.hpp"
#include "../dto/arm-dto.hpp"
#include "../dto/feedback-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Mission Control Testing")
    {
        MissionControlHandler mc_handler;
        arm_accelerometer_feedback mpu_feedback;
        motors_feedback arm_motors_feedback;
        hand_arguments hand_feedback;
        arm_arguments arm_feedback;

        SECTION("should return default arm status on startup")
        {
            std::string expected_formatted_rover_status =
                "arm?heartbeat_count=0&is_operational=0&speed=0&joint_mode=S&rotunda_angle=0&shoulder_angle=0&elbow_angle=0&wrist_pitch_angle=0&wrist_roll_angle=0&hand_mode=I&pinky_angle=88&ring_angle=88&middle_angle=88&index_angle=88&thumb_angle=88";

            std::string actual_formatted_rover_status = mc_handler.CreateGETRequestParameterWithRoverStatus(arm_feedback);

            CHECK_EQ(expected_formatted_rover_status, actual_formatted_rover_status);
        }

        SECTION("should return default mission control data on startup despite imperfect command string")
        {
            // arm_arguments expected_args = {{0, 0, 5, 'S', 100, 100, 100, 100, 100}, {'I', 120, 120, 120, 120, 120}};
            arm_arguments expected_args;
            std::string example_mission_control_response =
                "asdfasdf{\"heartbeat_count\":0,\"is_operational\":0,\"speed\":5,\"joint_mode\":\"S\",\"joint_angles\":[100,100,100,100,100],\"hand_mode\":\"I\",\"hand_angles\":[120,120,120,120,120]}";

            arm_arguments actual_args = mc_handler.ParseMissionControlData(example_mission_control_response);

            CHECK_EQ(expected_args.joint_args.heartbeat_count, actual_args.joint_args.heartbeat_count);
            CHECK_EQ(expected_args.joint_args.is_operational, actual_args.joint_args.is_operational);
            CHECK_EQ(expected_args.joint_args.speed, actual_args.joint_args.speed);
            CHECK_EQ(expected_args.joint_args.mode, actual_args.joint_args.mode);
            CHECK_EQ(expected_args.joint_args.rotunda_angle, actual_args.joint_args.rotunda_angle);
            CHECK_EQ(expected_args.joint_args.shoulder_angle, actual_args.joint_args.shoulder_angle);
            CHECK_EQ(expected_args.joint_args.elbow_angle, actual_args.joint_args.elbow_angle);
            CHECK_EQ(expected_args.joint_args.wrist_pitch_angle, actual_args.joint_args.wrist_pitch_angle);
            CHECK_EQ(expected_args.joint_args.wrist_roll_angle, actual_args.joint_args.wrist_roll_angle);
            CHECK_EQ(expected_args.hand_args.mode, actual_args.hand_args.mode);
            CHECK_EQ(expected_args.hand_args.pinky_angle, actual_args.hand_args.pinky_angle);
            CHECK_EQ(expected_args.hand_args.ring_angle, actual_args.hand_args.ring_angle);
            CHECK_EQ(expected_args.hand_args.middle_angle, actual_args.hand_args.middle_angle);
            CHECK_EQ(expected_args.hand_args.index_angle, actual_args.hand_args.index_angle);
            CHECK_EQ(expected_args.hand_args.thumb_angle, actual_args.hand_args.thumb_angle);
        }

        SECTION("should successfully handle multiple mission control responses")
        {
            arm_arguments expected_args = {{0, 1, 5, 'S', 100, 100, 100, 100, 100}, {'I', 120, 120, 120, 120, 120}};
            std::string example_mission_control_response =
                "{\"heartbeat_count\":0,\"is_operational\":1,\"speed\":5,\"joint_mode\":\"S\",\"joint_angles\":[100,100,100,100,100],\"hand_mode\":\"I\",\"hand_angles\":[120,120,120,120,120]}{\"heartbeat_count\":0,\"is_operational\":0,\"speed\":5,";

            arm_arguments actual_args = mc_handler.ParseMissionControlData(example_mission_control_response);

            CHECK_EQ(expected_args.joint_args.is_operational, actual_args.joint_args.is_operational);
        }
    }
}
