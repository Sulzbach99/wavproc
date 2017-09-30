#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define ARGS "ioxx"

int main(int argc, char *argv[])
{
    audio_t AUDIO;

    if (!TreatArgs(argc, argv, ARGS))
    {
        fprintf(stderr, "Could not understand argument(s)\n");
        exit(0);
    }

    if (!LoadAudio(&AUDIO))
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    Rev(&AUDIO);

    Write(&AUDIO);

    exit(1);
}