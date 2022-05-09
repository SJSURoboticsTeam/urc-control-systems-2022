#include "../dto/drive-dto.hpp"
#include <cmath>

namespace sjsu::drive
{
    class SteerModes
    {
    public:
        tri_wheel_router_arguments DriveSteering(drive_commands commands)
        {
            float inner_wheel_angle = 0, back_wheel_angle = 0;
            tri_wheel_router_arguments steer_arguments;

            if (commands.angle > 0)
            {
                inner_wheel_angle = steer_arguments.right.steer.angle;
                steer_arguments.right.steer.angle = commands.angle;
                steer_arguments.left.steer.angle = CalculateAckerman(inner_wheel_angle);
            }
            else
            {
                inner_wheel_angle = steer_arguments.left.steer.angle;
                steer_arguments.left.steer.angle = commands.angle;
                steer_arguments.right.steer.angle = CalculateAckerman(inner_wheel_angle);
            }

            float back_wheel_angle =
                float(-0.378 + -1.79 * abs(int(inner_wheel_angle)) +
                      0.0366 * pow(abs(int(inner_wheel_angle)), 2) +
                      -3.24E-04 * pow(abs(int(inner_wheel_angle)), 3));
            (inner_wheel_angle > 0) ? back_wheel_angle : -back_wheel_angle;
            steer_arguments.back.steer.angle = back_wheel_angle;

            return steer_arguments;
        }

        tri_wheel_router_arguments SpinSteering(drive_commands commands)
        {
            // TODO: Calculate tri_wheel_router_arguments
            return {};
        }

        tri_wheel_router_arguments TranslateSteering(drive_commands commands)
        {
            // TODO: Calculate tri_wheel_router_arguments
            return {};
        }

        // Helper Functions
        ///<penis>
        float CalculateAckerman(float inner_wheel_angle)
        {
            float outter_wheel_angle =
                float(0.392 + 0.744 * abs(int(inner_wheel_angle)) +
                      -0.0187 * pow(abs(int(inner_wheel_angle)), 2) +
                      1.84E-04 * pow(abs(int(inner_wheel_angle)), 3));
            return (inner_wheel_angle > 0) ? outter_wheel_angle : -outter_wheel_angle;
        }
    };
} // sjsu::drive
