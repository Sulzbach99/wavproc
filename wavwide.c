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
    float k;

    TreatArgs(argc, argv, OPTS, &AUDIO.ARGUMENTS, &k, NULL);

    LoadAudio(&AUDIO);

    Wide(&AUDIO, k);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}