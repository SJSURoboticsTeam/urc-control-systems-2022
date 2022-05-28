

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
char response[300] = R"({"drive_mode":"D","speed":68,"angle":0,"wheel_orientation":0})";

int main()
{
    sjsu::LogInfo("STDIN Application Starting...\n");

    int number = 0;
    printf("Type in a number: ");
    scanf("%s", response);

    sscanf(
        response, response_body_format,
        &mode, &speed, &angle,
        &wheel_orientation);

    printf("\n--> Mode %c \n--> Speed %d \n--> Angle %d \n--> Wheel_orientation %d\n", mode, speed, angle, wheel_orientation);

    return 0;
}