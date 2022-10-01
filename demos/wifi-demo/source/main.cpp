#include "../../common/esp.hpp"
#include "../../subsystem-drive/dto/drive-dto.hpp"
#include "../../subsystem-drive/implementations/mission-control-handler.hpp"

using namespace sjsu::drive;

int main()
{
    MissionControlHandler mission_control;
    drive_commands commands;
    sjsu::common::Esp esp;

    sjsu::LogInfo("Starting ESP8266 demo...");
    try
    {
        esp.Connect();
        std::string response = esp.GetCommands("drive");
        printf("Response:\n %.*s\n", response.size(), response.data());
        commands = mission_control.ParseMissionControlData(response);
        printf("\nParsed: ");
        commands.Print();
        esp.Disconnect();
    }
    catch (std::exception &e)
    {
        sjsu::LogError("Uncaught error!", e);
        esp.Disconnect();
    }
    return 0;
}