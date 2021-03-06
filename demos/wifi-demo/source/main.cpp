#include "../../common/esp.hpp"
#include "../../subsystem-drive/implementations/mission-control-handler.hpp"

using namespace sjsu::drive;

int main()
{
    MissionControlHandler mission_control;
    drive_commands commands;
    sjsu::common::Esp esp;
    sjsu::LogInfo("Starting ESP...");
    esp.Connect();
    while (1)
    {
        try
        {
            std::string endpoint = mission_control.CreateGETRequestParameterWithRoverStatus();
            std::string response = esp.GetCommands(endpoint);
            commands = mission_control.ParseMissionControlData(response);
            sjsu::Delay(2s);
        }
        catch (std::exception &e)
        {
            sjsu::LogError("Uncaught error in main() - Stopping Rover!");
            if (!esp.IsConnected())
            {
                esp.Connect();
            }
        }
    }

    return 0;
}