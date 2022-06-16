#include "testing/testing_frameworks.hpp"
#include "utility/log.hpp"
#include "implementations/mission-control-handler.hpp"
#include "../dto/arm-dto.hpp"

namespace sjsu::arm
{
    TEST_CASE("Mission Control Testing")
    {
        MissionControlHandler mc_handler;
        imu_accelerometers_feedback mpu_feedback;
        motors_feedback arm_motors_feedback;
        hand_arguments hand_feedback;
        arm_commands arm_feedback;

        SECTION("should return default arm status on startup")
        {
            std::string expected_formatted_rover_status =
                "?heartbeat_count=0&is_operational=0&arm_mode=A&hand_mode=A&rotunda_speed=0"
                "&shoulder_speed=0&elbow_speed=0&wrist_speed=0&battery=0&rotunda_angle=0&shoulder_angle=0&elbow_angle=0&wrist_"
                "roll=0&wrist_pitch=0&pinky_angle=0&ring_angle=0&middle_angle=0&"
                "pointer_angle=0&thumb_angle=0&rountda_accel_x=0&rountda_accel_y=0&rountda_accel_z=0"
                "&shoulder_accel_x=0&shoulder_accel_y=0&shoulder_accel_z=0"
                "&elbow_accel_x=0&elbow_accel_y=0&elbow_accel_z=0"
                "&wrist_accel_x=0&wrist_accel_y=0&wrist_accel_z=0";

            std::string actual_formatted_rover_status = mc_handler.CreateGETRequestParameterWithRoverStatus(mpu_feedback, arm_motors_feedback, hand_feedback, arm_feedback);

            CHECK_EQ(expected_formatted_rover_status, actual_formatted_rover_status);
        }
    }
}
