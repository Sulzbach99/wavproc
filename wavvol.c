#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"

void Mult(signed short *v, unsigned int a, unsigned int b)
{
    for (unsigned int i = a; i <= b; i++)
        v[i] *= Volume;
}

int main(int argc, char *argv[])
{
    if (!TreatArgs(argc, argv))
    {
        fprintf(stderr, "Could not understand argument(s)\n");
        exit(0);
    }

    if (!LoadAudio())
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    for (unsigned int k = 0; k < AUDIO.ChannelNr; k++)
        Mult(AUDIO.Data[k], 0, (AUDIO.SubChunk2Size / AUDIO.BlockAlign) - 1);

    Write();

    exit(1);
}