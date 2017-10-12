#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define OPTS "ilo~"

int main(int argc, char *argv[])
{
    audio_t AUDIO;
    float Volume;

    TreatArgs(argc, argv, OPTS, &AUDIO.ARGUMENTS, &Volume, NULL);

    LoadAudio(&AUDIO);

    Vol(&AUDIO, Volume);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}