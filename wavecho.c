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

    TreatArgs(argc, argv, OPTS, &AUDIO.ARGUMENTS, &Aten, &Delay);

    LoadAudio(&AUDIO);

    Echo(&AUDIO, Aten, Delay);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}