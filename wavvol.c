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

    AUDIO.INPUT = stdin;
    AUDIO.OUTPUT = stdout;

    TreatArgs(argc, argv, OPTS, &AUDIO.INPUT, &AUDIO.OUTPUT, &Volume, NULL);

    LoadAudio(&AUDIO);

    Vol(&AUDIO, Volume);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}