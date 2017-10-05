#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define POSSIBLE_ARGS "ioxx"

int main(int argc, char *argv[])
{
    audio_t AUDIO;

    PreSet(&AUDIO.ARGUMENTS);
    SetInputs(&AUDIO.ARGUMENTS);
    TreatArgs(argc, argv, POSSIBLE_ARGS, &AUDIO.ARGUMENTS, NULL, NULL);

    if (!LoadAudio(&AUDIO, &ARGUMENTS))
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    AUDIO.ARGUMENTS.Revert = 1;
    TreatAudio(&AUDIO);

    Write(&AUDIO);

    exit(1);
}