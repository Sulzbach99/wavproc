#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "audiotreat.h"

void Revert()
{
    signed short aux;
    unsigned int a, b;

    for (unsigned int k = 0; k < AUDIO.ChannelNr; k++)
    {
        a = 0;
        b = AUDIO.SubChunk2Size / AUDIO.BlockAlign - 1;
        while (a < b)
        {
            aux = AUDIO.Data[k][a];
            AUDIO.Data[k][a] = AUDIO.Data[k][b];
            AUDIO.Data[k][b] = aux;

            a++;
            b--;
        }
    }
}