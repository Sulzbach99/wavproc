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

    TreatArgs(argc, argv, OPTS, &AUDIO.ARGUMENTS, &AUDIO.ARGUMENTS.Aten, &AUDIO.ARGUMENTS.Delay);
    if (!AUDIO.ARGUMENTS.Delay)
        AUDIO.ARGUMENTS.Delay = 1000;

    LoadAudio(&AUDIO);

    TreatAudio(&AUDIO);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}