#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "audiotreat.h"

void Rev(audio_t *AUDIO)
{
    signed short aux;
    unsigned int a, b;

    for (unsigned int k = 0; k < AUDIO->ChannelNr; k++)
    {
        a = 0;
        b = AUDIO->SubChunk2Size / AUDIO->BlockAlign - 1;
        while (a < b)
        {
            aux = AUDIO->Data[k][a];
            AUDIO->Data[k][a] = AUDIO->Data[k][b];
            AUDIO->Data[k][b] = aux;

            a++;
            b--;
        }
    }
}

void Vol(audio_t *AUDIO)
{
    for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
        for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
            AUDIO->Data[i][j] *= Volume;
}

void AutoVol(audio_t *AUDIO)
{
    signed short max = AUDIO->Data[0][0];

    for (unsigned int k = 1; k < AUDIO->SubChunk2Size / AUDIO->BlockAlign; k++)
        if (AUDIO->Data[0][k] > max)
            max = AUDIO->Data[0][k];

    for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
        for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
            AUDIO->Data[i][j] = (AUDIO->Data[i][j] * 32767) / max;
}

void Del()
{
}