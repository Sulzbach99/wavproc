#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

int main(int argc, char *argv[])
{
    if (!TreatArgs(argc, argv))
    {
        fprintf(stderr, "Could not understand argument(s)\n");
        fprintf(stderr, "e.g. wavinfo -i [input] -o [output]\n");
        exit(0);
    }

    if (!LoadAudio())
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    for (unsigned int k = 0; k < AUDIO.ChannelNr; k++)
        Revert(AUDIO.Data[k], 0, (AUDIO.SubChunk2Size / AUDIO.BlockAlign) - 1);

    Write();

    exit(1);
}