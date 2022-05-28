

#include "utility/log.hpp"

const char response_body_format[] =
    "\r\n\r\n{\n"
    "  \"drive_mode\": \"%c\",\n"
    "  \"speed\": %d,\n"
    "  \"angle\": %d\n"
    "  \"wheel_orientation\": %d,\n"
    "}";

char mode;
int speed, angle, wheel_orientation;

int main()
{
    sjsu::LogInfo("STDIN Application Starting...\n");

    int number = 0;
    printf("Type in a number: ");

    sscanf(
        response_body_format,
        &mode, &speed, &angle,
        &wheel_orientation);

    printf("\n--> Mode %c\n \n--> Speed %d\n \n--> Angle %d\n \n--> Wheel_orientation %d\n", mode, speed, angle, wheel_orientation);

    return 0;
}