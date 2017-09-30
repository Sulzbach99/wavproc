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
    arguments_t ARGUMENTS;

    if (!TreatArgs(argc, argv, POSSIBLE_ARGS, &ARGUMENTS, NULL))
    {
        fprintf(stderr, "Could not understand argument(s)\n");
        exit(0);
    }

    if (!LoadAudio(&AUDIO, &ARGUMENTS))
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    ARGUMENTS.Revert = 1;
    TreatAudio(&AUDIO, &ARGUMENTS);

    Write(&AUDIO, &ARGUMENTS);

    exit(1);
}