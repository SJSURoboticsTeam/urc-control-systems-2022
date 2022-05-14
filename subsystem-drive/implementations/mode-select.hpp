#include "../dto/drive-dto.hpp"
#include "../steer-modes.hpp"

namespace sjsu::drive
{
    class ModeSelect
    {
    public:
        tri_wheel_router_arguments SelectMode(drive_commands commands)
        {
            switch (commands.mode)
            {
            case 'D':
                return SteerModes::DriveSteering(commands);
                break;
            case 'S':
                return SteerModes::SpinSteering(commands);
                break;
            case 'T':
                return SteerModes::TurnSteering(commands);
                break;
            default:
                return tri_wheel_router_arguments{};
                break;
            }
        }

    private:
    };
}