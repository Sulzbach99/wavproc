#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "audiotreat.h"

void TreatAudio(audio_t *AUDIO)
{
    if (AUDIO->ARGUMENTS.Revert)
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

    if (AUDIO->ARGUMENTS.AutoVol)
    {
        signed short max = AUDIO->Data[0][0];

        for (unsigned int k = 1; k < AUDIO->SubChunk2Size / AUDIO->BlockAlign; k++)
            if (AUDIO->Data[0][k] > max)
                max = AUDIO->Data[0][k];

        AUDIO->ARGUMENTS.Volume = 32767.0 / max;
    }

    if (AUDIO->ARGUMENTS.Volume != 1.0)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
                AUDIO->Data[i][j] *= AUDIO->ARGUMENTS.Volume;

    if (AUDIO->ARGUMENTS.Wide != 1.0)
    {
        signed short diff;

        for (unsigned int k = 0; k < AUDIO->SubChunk2Size / AUDIO->BlockAlign; k++)
        {
            diff = AUDIO->Data[1][k] - AUDIO->Data[0][k];

            AUDIO->Data[1][k] += AUDIO->ARGUMENTS.Wide * diff;
            AUDIO->Data[0][k] -= AUDIO->ARGUMENTS.Wide * diff;
        }
    }
}