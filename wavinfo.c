#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define OPTS "io~~"

int main(int argc, char *argv[])
{
    audio_t AUDIO;

    TreatArgs(argc, argv, OPTS, &AUDIO.ARGUMENTS, NULL, NULL);

    LoadAudio(&AUDIO);

    GetInfo(AUDIO);

    exit(EXIT_SUCCESS);
}