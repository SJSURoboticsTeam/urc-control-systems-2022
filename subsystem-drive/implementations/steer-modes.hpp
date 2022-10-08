#pragma once
#include <cmath>
#include <algorithm>

#include "../dto/drive-dto.hpp"
#include "../dto/motor-feedback-dto.hpp"

namespace sjsu::drive
{
    class SteerModes
    {
    public:
        static constexpr float kLeftLegDriveOffset = 41;
        static constexpr float kRightLegDriveOffset = 200;
        static constexpr float kBackLegDriveOffset = 121;
        static constexpr float kLeftLegSpinOffset = 242;
        static constexpr float kRightLegSpinOffset = 0;
        static constexpr float kBackLegSpinOffset = 0;
        static constexpr float kLeftLegTranslateOffset = 0;

        static tri_wheel_router_arguments DriveSteering(drive_commands commands, motor_feedback steering_motor_data)
        {
            float outter_wheel_angle = 0, back_wheel_angle = 0;
            tri_wheel_router_arguments steer_arguments;

            if (commands.angle > 0)
            {
                outter_wheel_angle = -commands.angle;
                steer_arguments.left.steer.angle = outter_wheel_angle;
                steer_arguments.right.steer.angle = CalculateAckermann(outter_wheel_angle);
            }
            else if (commands.angle < 0)
            {
                outter_wheel_angle = -commands.angle;
                steer_arguments.right.steer.angle = outter_wheel_angle;
                steer_arguments.left.steer.angle = CalculateAckermann(outter_wheel_angle);
            }
            if (commands.angle == 0)
            {
                steer_arguments.back.steer.angle = 0;
                steer_arguments.left.steer.angle = 0;
                steer_arguments.right.steer.angle = 0;
            }
            else
            {
                outter_wheel_angle = -outter_wheel_angle;
                back_wheel_angle =
                    float(-.0474 + -1.93 * abs(int(outter_wheel_angle)) +
                          -.0813 * pow(abs(int(outter_wheel_angle)), 2) +
                          .000555 * pow(abs(int(outter_wheel_angle)), 3));
                back_wheel_angle = (outter_wheel_angle > 0) ? -back_wheel_angle : back_wheel_angle;
                steer_arguments.back.steer.angle = back_wheel_angle;
            }

            if (steering_motor_data.left_steer_angle > 0)
            {
                sjsu::LogInfo("%f", steering_motor_data.left_steer_angle);
                steer_arguments.right.hub.speed = -GetInnerWheelHubSpeed(commands.speed, outter_wheel_angle);
                steer_arguments.left.hub.speed = -GetOutterWheelHubSpeed(commands.speed, outter_wheel_angle);
                steer_arguments.back.hub.speed = GetBackWheelHubSpeed(commands.speed, outter_wheel_angle);
            }

            else if (steering_motor_data.left_steer_angle < 0)
            {
                sjsu::LogInfo("%f", steering_motor_data.left_steer_angle);
                steer_arguments.left.hub.speed = -GetInnerWheelHubSpeed(commands.speed, outter_wheel_angle);
                steer_arguments.right.hub.speed = -GetOutterWheelHubSpeed(commands.speed, outter_wheel_angle);
                steer_arguments.back.hub.speed = GetBackWheelHubSpeed(commands.speed, outter_wheel_angle);
            }
            else
            {
                sjsu::LogInfo("here3");
                steer_arguments.left.hub.speed = -commands.speed;
                steer_arguments.right.hub.speed = -commands.speed;
                steer_arguments.back.hub.speed = commands.speed;
            }

            // adding the offsets to put it into the base drive mode
            steer_arguments.left.steer.angle += kLeftLegDriveOffset;
            steer_arguments.right.steer.angle += kRightLegDriveOffset;
            steer_arguments.back.steer.angle += kBackLegDriveOffset;
            return steer_arguments;
        }

        static tri_wheel_router_arguments SpinSteering(drive_commands commands)
        {
            tri_wheel_router_arguments temp;
            temp.back.steer.angle = kBackLegSpinOffset;
            temp.left.steer.angle = kLeftLegSpinOffset;
            temp.right.steer.angle = kRightLegSpinOffset;
            temp.back.hub.speed = commands.speed;
            temp.left.hub.speed = -commands.speed;
            temp.right.hub.speed = commands.speed;

            return temp;
        }

        static tri_wheel_router_arguments TranslateSteering(drive_commands commands)
        {
            tri_wheel_router_arguments steer_arguments;

            steer_arguments.left.steer.angle = commands.angle + kLeftLegDriveOffset;
            steer_arguments.right.steer.angle = commands.angle + kRightLegDriveOffset;
            steer_arguments.back.steer.angle = commands.angle + kBackLegDriveOffset;

            steer_arguments.left.hub.speed = -commands.speed;
            steer_arguments.right.hub.speed = -commands.speed;
            steer_arguments.back.hub.speed = commands.speed;

            return steer_arguments;
        }

    private:
        /// Ackerman steering equation to compute outter wheel angle
        static float CalculateAckermann(float outter_wheel_angle)
        {
            float inner_wheel_angle =
                float(-.583 + 1.97 * abs(int(outter_wheel_angle)) +
                      -.224 * pow(abs(int(outter_wheel_angle)), 2) +
                      .0278 * pow(abs(int(outter_wheel_angle)), 3));
            return (outter_wheel_angle > 0) ? inner_wheel_angle : -inner_wheel_angle;
        }

        static float GetInnerWheelHubSpeed(float outter_wheel_speed, float outter_wheel_angle)
        {
            // clamps the inner wheel speed to be no faster then what will mess up the
            // correct ackerman velocity this clamp will then ensure the same for the
            // back wheel speed since its based on this angle
            float ratio = GetOutterWheelRadius(outter_wheel_angle) /
                          GetInnerWheelRadius(outter_wheel_angle);
            // std::clamp(inner_wheel_speed, -100 / ratio, 100 / ratio);
            return outter_wheel_speed;
        }

        static float GetBackWheelHubSpeed(float outter_wheel_speed, float outter_wheel_angle)
        {
            float ratio = GetBackWheelRadius(outter_wheel_angle) /
                          GetInnerWheelRadius(outter_wheel_angle);
            float back_wheel_speed = outter_wheel_speed * ratio;
            // std::clamp(inner_wheel_speed * ratio, -100 / ratio, 100 / ratio);
            return back_wheel_speed;
        }

        static float GetOutterWheelHubSpeed(float outter_wheel_speed, float outter_wheel_angle)
        {
            float ratio = GetOutterWheelRadius(outter_wheel_angle) /
                          GetInnerWheelRadius(outter_wheel_angle);
            return (outter_wheel_speed * ratio);
        }

        static float GetInnerWheelRadius(float outter_wheel_angle)
        {
            return (15 * pow(abs(outter_wheel_angle), -.971));
        }

        static float GetBackWheelRadius(float outter_wheel_angle)
        {
            return (11.6 * pow(abs(outter_wheel_angle), -.698));
        }

        static float GetOutterWheelRadius(float outter_wheel_angle)
        {
            return (11.6 * pow(abs(outter_wheel_angle), -.616));
        }
    };
} // sjsu::drive
