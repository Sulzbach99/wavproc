#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define OPTS "ilot"

int main(int argc, char *argv[])
{
    audio_t AUDIO;
    float Aten, Delay;

    AUDIO.INPUT = stdin;
    AUDIO.OUTPUT = stdout;

    TreatArgs(argc, argv, OPTS, &AUDIO.INPUT, &AUDIO.OUTPUT, &Aten, &Delay);

    LoadAudio(&AUDIO);

    Echo(&AUDIO, Aten, Delay);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}