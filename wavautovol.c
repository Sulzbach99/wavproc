#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define POSSIBLE_ARGS "io~~"

int main(int argc, char *argv[])
{
    audio_t AUDIO;

    TreatArgs(argc, argv, POSSIBLE_ARGS, &AUDIO.ARGUMENTS, NULL, NULL);

    LoadAudio(&AUDIO);

    AUDIO.ARGUMENTS.AutoVol = 1;
    TreatAudio(&AUDIO);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}