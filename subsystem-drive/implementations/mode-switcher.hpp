#include "../dto/drive-dto.hpp"

namespace sjsu::drive
{
    class ModeSwitch
    {
    public:
        // Should handle all the logic for switching to new steer mode
        drive_commands SwitchSteerMode(drive_commands commands)
        {
            switch (commands.mode)
            {
            case /* constant-expression */:
                /* code */
                break;

            default:
                break;
            }
        }

    private:
    };
}