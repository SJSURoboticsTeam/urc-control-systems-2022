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
                "?heartbeat_count=0&is_operational=0&arm_mode=%c&hand_mode=%c&rotunda_speed=%d"
                "&shoulder_speed%d&elbow_speed%d&wrist_speed%d&battery=0&rotunda_angle=%d&shoulder_angle=%d&elbow_angle=%d&wrist_"
                "roll=%d&wrist_pitch=%d&pinky_angle=%d&ring_angle=%d&middle_angle=%d&"
                "pointer_angle=%d&thumb_angle=%d"
                "&rountda_accel_x=%d&rountda_accel_y=%d&rountda_accel_z=%d"
                "&shoulder_accel_x=%d&shoulder_accel_y=%d&shoulder_accel_z=%d"
                "&elbow_accel_x=%d&elbow_accel_y=%d&elbow_accel_z=%d"
                "&wrist_accel_x=%d&wrist_accel_y=%d&wrist_accel_z=%d";

            std::string actual_formatted_rover_status = mc_handler.CreateGETRequestParameterWithRoverStatus(mpu_feedback, arm_motors_feedback, hand_feedback, arm_feedback);

            CHECK_EQ(expected_formatted_rover_status, actual_formatted_rover_status);
        }
    }
}