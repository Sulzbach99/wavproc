#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "audiotreat.h"

void TreatAudio(audio_t *AUDIO, arguments_t *ARGUMENTS)
{
    if (ARGUMENTS->Revert)
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

    if (ARGUMENTS->AutoVol)
    {
        signed short max = AUDIO->Data[0][0];

        for (unsigned int k = 1; k < AUDIO->SubChunk2Size / AUDIO->BlockAlign; k++)
            if (AUDIO->Data[0][k] > max)
                max = AUDIO->Data[0][k];

        ARGUMENTS->Volume = 32767 / max;
    }

    if (ARGUMENTS->Volume != 1.0)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
                AUDIO->Data[i][j] *= ARGUMENTS->Volume;

    if (ARGUMENTS->Wide != 1.0)
    {
        signed short diff;

        for (unsigned int k = 0; k < AUDIO->SubChunk2Size / AUDIO->BlockAlign; k++)
        {
            diff = AUDIO->Data[1][k] - AUDIO->Data[0][k];

            AUDIO->Data[1][k] += ARGUMENTS->Wide * diff;
            AUDIO->Data[0][k] -= ARGUMENTS->Wide * diff;
        }
    }
}