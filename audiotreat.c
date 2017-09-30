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

void Mult()
{
    for (unsigned int i = 0; i < AUDIO.ChannelNr; i++)
        for (unsigned int j = 0; j < AUDIO.SubChunk2Size / AUDIO.BlockAlign; j++)
            AUDIO.Data[i][j] *= Volume;
}