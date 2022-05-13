#include "../dto/drive-dto.hpp"
#include <cmath>
#include <algorithm>

namespace sjsu::drive
{
    class SteerModes
    {
    public:
    static constexpr float kspin_angle = 120;

        static tri_wheel_router_arguments DriveSteering(drive_commands commands)
        {
            float inner_wheel_angle = 0, back_wheel_angle = 0;
            tri_wheel_router_arguments steer_arguments;

            if (commands.angle > 0)
            {
                inner_wheel_angle = commands.angle;
                steer_arguments.right.steer.angle = inner_wheel_angle;
                steer_arguments.left.steer.angle = CalculateAckermann(inner_wheel_angle);
            }
            else if (commands.angle < 0)
            {
                inner_wheel_angle = commands.angle;
                steer_arguments.left.steer.angle = inner_wheel_angle;
                steer_arguments.right.steer.angle = CalculateAckermann(inner_wheel_angle);
            }
            if (commands.angle == 0)
            {
                steer_arguments.back.steer.angle = 0;
                steer_arguments.left.steer.angle = 0;
                steer_arguments.right.steer.angle = 0;
            }
            else
            {
                back_wheel_angle =
                    float(-0.378 + -1.79 * abs(int(inner_wheel_angle)) +
                          0.0366 * pow(abs(int(inner_wheel_angle)), 2) +
                          -3.24E-04 * pow(abs(int(inner_wheel_angle)), 3));
                (inner_wheel_angle > 0) ? back_wheel_angle : -back_wheel_angle;
                steer_arguments.back.steer.angle = back_wheel_angle;
            }

            if (inner_wheel_angle > 0)
            {
                steer_arguments.right.hub.speed = -GetInnerWheelHubSpeed(commands.speed, inner_wheel_angle);
                steer_arguments.left.hub.speed = -GetOutterWheelHubSpeed(commands.speed, inner_wheel_angle);
                steer_arguments.back.hub.speed = GetBackWheelHubSpeed(commands.speed, inner_wheel_angle);
            }

            else if (inner_wheel_angle < 0)
            {
                steer_arguments.left.hub.speed = -GetInnerWheelHubSpeed(commands.speed, inner_wheel_angle);
                steer_arguments.right.hub.speed = -GetOutterWheelHubSpeed(commands.speed, inner_wheel_angle);
                steer_arguments.back.hub.speed = GetBackWheelHubSpeed(commands.speed, inner_wheel_angle);
            }
            else
            {
                steer_arguments.left.hub.speed = -commands.speed;
                steer_arguments.right.hub.speed = -commands.speed;
                steer_arguments.back.hub.speed = commands.speed;
            }

            return steer_arguments;
        }

        static tri_wheel_router_arguments SpinSteering(drive_commands commands)
        {
            tri_wheel_router_arguments temp;
            temp.back.steer.angle = kspin_angle;
            temp.left.steer.angle = -kspin_angle;
            temp.right.steer.angle = -kspin_angle;
            temp.back.hub.speed = commands.speed;
            temp.left.hub.speed = -commands.speed;
            temp.right.hub.speed = -commands.speed;

            return temp;
        }

        static tri_wheel_router_arguments TranslateSteering(drive_commands commands)
        {
            tri_wheel_router_arguments steer_arguments;

            steer_arguments.left.steer.angle = commands.angle;
            steer_arguments.right.steer.angle = commands.angle + 60;
            steer_arguments.back.steer.angle = commands.angle + 110;

            steer_arguments.left.hub.speed = commands.speed;
            steer_arguments.right.hub.speed = commands.speed;
            steer_arguments.back.hub.speed = commands.speed;

            return steer_arguments;
        }

    private:
        /// Ackerman steering equation to compute outter wheel angle
        static float CalculateAckermann(float inner_wheel_angle)
        {
            float outter_wheel_angle =
                float(0.392 + 0.744 * abs(int(inner_wheel_angle)) +
                      -0.0187 * pow(abs(int(inner_wheel_angle)), 2) +
                      1.84E-04 * pow(abs(int(inner_wheel_angle)), 3));
            return (inner_wheel_angle > 0) ? outter_wheel_angle : -outter_wheel_angle;
        }

        static float GetInnerWheelHubSpeed(float inner_wheel_speed, float inner_wheel_angle)
        {
            // clamps the inner wheel speed to be no faster then what will mess up the
            // correct ackerman velocity this clamp will then ensure the same for the
            // back wheel speed since its based on this angle
            float ratio = GetOutterWheelRadius(inner_wheel_angle) /
                          GetInnerWheelRadius(inner_wheel_angle);
            // std::clamp(inner_wheel_speed, -100 / ratio, 100 / ratio);
            return inner_wheel_speed;
        }

        static float GetBackWheelHubSpeed(float inner_wheel_speed, float inner_wheel_angle)
        {
            float ratio = GetBackWheelRadius(inner_wheel_angle) /
                          GetInnerWheelRadius(inner_wheel_angle);
            float back_wheel_speed = inner_wheel_speed * ratio;
            // std::clamp(inner_wheel_speed * ratio, -100 / ratio, 100 / ratio);
            return back_wheel_speed;
        }

        static float GetOutterWheelHubSpeed(float inner_wheel_speed, float inner_wheel_angle)
        {
            float ratio = GetOutterWheelRadius(inner_wheel_angle) /
                          GetInnerWheelRadius(inner_wheel_angle);
            return (inner_wheel_speed * ratio);
        }

        static float GetInnerWheelRadius(float inner_wheel_angle)
        {
            return (15 * pow(abs(inner_wheel_angle), -.971));
        }

        static float GetBackWheelRadius(float inner_wheel_angle)
        {
            return (11.6 * pow(abs(inner_wheel_angle), -.698));
        }

        static float GetOutterWheelRadius(float inner_wheel_angle)
        {
            return (11.6 * pow(abs(inner_wheel_angle), -.616));
        }
    };
} // sjsu::drive
