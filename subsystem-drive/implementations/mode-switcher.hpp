#include "../dto/drive-dto.hpp"
#include "../steer-modes.hpp"

namespace sjsu::drive
{
    class ModeSwitch
    {
    public:
        // Should handle all the logic for switching to new steer mode
        drive_commands SwitchSteerMode(drive_commands commands, bool stopped)
        {
            if (current_mode != commands.mode)
            {
                // Set all wheel speed equal to 0
                commands.speed = 0;
                commands.angle = 0;
                commands.wheel_orientation = 0;
                // Set rover to home position using home function
            }
            current_mode = commands.mode;
            return commands;
        }

    private:
        char current_mode = 'D';
    };
}