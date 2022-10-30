#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>

#include "application.h"

int main(int argc, char **argv)
{
    char IPadd[32] = "127.0.0.1";

    //printf("Enter IPAddress: ");

    //scanf(" %s%*c", IPadd);

    application(IPadd);

    return 0;
}