#include <stdio.h>
#include <stdlib.h>
#include "acesso.h"

int main()
{
    audio_t WAV;
    signed char setup;

    setup = LoadAudio(WAV);
    if (!setup)
    {
        perror("LoadAudio Error");
        exit(0);
    }



    exit(1);
}