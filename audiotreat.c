#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "access.h"
#include "audiotreat.h"

void GetInfo(audio_t AUDIO)
{
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "riff tag       : \"%s\"\n", AUDIO.ChunkID);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "riff size      : %i\n", AUDIO.ChunkSize);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "wave tag       : \"%s\"\n", AUDIO.Format);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "form tag       : \"%s\"\n", AUDIO.SubChunk1ID);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "fmt_size       : %i\n", AUDIO.SubChunk1Size);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "audio_format   : %i\n", AUDIO.AudioFormat);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "num_channels   : %i\n", AUDIO.ChannelNr);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "sample_rate    : %i\n", AUDIO.SampleRate);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "byte_rate      : %i\n", AUDIO.ByteRate);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "block_align    : %i\n", AUDIO.BlockAlign);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "bits_per_sample: %i\n", AUDIO.BitsPerSample);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "data tag       : \"%s\"\n", AUDIO.SubChunk2ID);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "data size      : %i\n", AUDIO.SubChunk2Size);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "samples/channel: %i\n", AUDIO.SamplesPerChannel);

    fclose(AUDIO.ARGUMENTS.OUTPUT);
}

void TreatAudio(audio_t *AUDIO)
{
    if (AUDIO->ARGUMENTS.Revert)
    {
        signed short aux;
        unsigned int a, b;

        for (unsigned int k = 0; k < AUDIO->ChannelNr; k++)
        {
            a = 0;
            b = AUDIO->SamplesPerChannel - 1;
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

    if (AUDIO->ARGUMENTS.Wide != 1.0)
    {
        signed short diff;

        for (unsigned int k = 0; k < AUDIO->SamplesPerChannel; k++)
        {
            diff = AUDIO->Data[1][k] - AUDIO->Data[0][k];

            AUDIO->Data[1][k] += AUDIO->ARGUMENTS.Wide * diff;
            AUDIO->Data[0][k] -= AUDIO->ARGUMENTS.Wide * diff;
        }

        AUDIO->ARGUMENTS.AutoVol = 1;
    }

    if (AUDIO->ARGUMENTS.Delay)
    {
        unsigned int Aux = (AUDIO->SampleRate * AUDIO->ARGUMENTS.Delay) / 1000;

        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            for (unsigned int j = 0; j + Aux < AUDIO->SamplesPerChannel; j++)
                AUDIO->Data[i][j+Aux] += AUDIO->Data[i][j] * AUDIO->ARGUMENTS.Aten;

        AUDIO->ARGUMENTS.AutoVol = 1;
    }

    if (AUDIO->ARGUMENTS.AutoVol)
    {
        signed int max = AUDIO->Data[0][0];

        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            for (unsigned int j = 0; j < AUDIO->SamplesPerChannel; j++)
                if (AUDIO->Data[i][j] > max)
                    max = abs(AUDIO->Data[i][j]);

        AUDIO->ARGUMENTS.Volume = 32767.0 / max;
    }

    if (AUDIO->ARGUMENTS.Volume != 1.0)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            for (unsigned int j = 0; j < AUDIO->SamplesPerChannel; j++)
                AUDIO->Data[i][j] *= AUDIO->ARGUMENTS.Volume;
}

audio_t *CatAudios(audio_t *AUDIO, char AudNum)
{
    audio_t *ptr = Malloc(sizeof(audio_t));
    unsigned long col = 0;

    strcpy(ptr->ChunkID, "RIFF");
    strcpy(ptr->Format, "WAVE");
    strcpy(ptr->SubChunk1ID, "fmt ");
    ptr->SubChunk1Size = 16;
    ptr->AudioFormat = 1;
    ptr->ChannelNr = AUDIO[0].ChannelNr;
    ptr->SampleRate = 44100;
    ptr->ByteRate = AUDIO[0].ByteRate;
    ptr->BlockAlign = AUDIO[0].BlockAlign;
    ptr->BitsPerSample = 16;
    strcpy(ptr->SubChunk2ID, "data");
    ptr->SubChunk2Size = AUDIO[0].SubChunk2Size;

    for (unsigned int k = 1; k < AudNum; k++)
    {
        ptr->SubChunk2Size += AUDIO[k].SubChunk2Size;

        if (ptr->ChannelNr > AUDIO[k].ChannelNr)
        {
            ptr->ChannelNr = AUDIO[k].ChannelNr;
            ptr->ByteRate = AUDIO[k].ByteRate;
            ptr->BlockAlign = AUDIO[k].BlockAlign;
        }
    }
    ptr->ChunkSize = 36 + ptr->SubChunk2Size;
    ptr->SamplesPerChannel = ptr->SubChunk2Size / ptr->BlockAlign;

    ptr->Data = Malloc(ptr->ChannelNr * sizeof(short*));
    for (unsigned int l = 0; l < ptr->ChannelNr; l++)
        ptr->Data[l] = Malloc(ptr->SubChunk2Size / ptr->ChannelNr);

    for (unsigned int m = 0; m < AudNum; m++)
        for (unsigned int j = 0; j < AUDIO[m].SamplesPerChannel; j++)
        {
            for (unsigned int i = 0; i < ptr->ChannelNr; i++)
                ptr->Data[i][col] = AUDIO[m].Data[i][j];
            col++;
        }

    free(AUDIO);

    return ptr;
}

audio_t *MixAudios(audio_t *AUDIO, char AudNum)
{
    audio_t *ptr = Malloc(sizeof(audio_t));

    strcpy(ptr->ChunkID, "RIFF");
    strcpy(ptr->Format, "WAVE");
    strcpy(ptr->SubChunk1ID, "fmt ");
    ptr->SubChunk1Size = 16;
    ptr->AudioFormat = 1;
    ptr->ChannelNr = AUDIO[0].ChannelNr;
    ptr->SampleRate = 44100;
    ptr->BitsPerSample = 16;
    strcpy(ptr->SubChunk2ID, "data");
    ptr->SubChunk2Size = AUDIO[0].SubChunk2Size;

    for (unsigned int k = 1; k < AudNum; k++)
    {
        if (ptr->ChannelNr > AUDIO[k].ChannelNr)
            ptr->ChannelNr = AUDIO[k].ChannelNr;

        if (ptr->SamplesPerChannel < AUDIO[k].SamplesPerChannel)
            ptr->SamplesPerChannel = AUDIO[k].SamplesPerChannel;
    }
    ptr->BlockAlign = ptr->ChannelNr * (ptr->BitsPerSample / 8);
    ptr->ByteRate = ptr->SampleRate * ptr->BlockAlign;
    ptr->SubChunk2Size = ptr->SamplesPerChannel * ptr->BlockAlign;
    ptr->ChunkSize = 36 + ptr->SubChunk2Size;

    ptr->Data = Malloc(ptr->ChannelNr * sizeof(short*));
    for (unsigned int l = 0; l < ptr->ChannelNr; l++)
        ptr->Data[l] = Malloc(ptr->SubChunk2Size / ptr->ChannelNr);

    for (unsigned int i = 0; i < ptr->ChannelNr; i++)
        for (unsigned int j = 0; j < ptr->SubChunk2Size / ptr->BlockAlign; j++)
            ptr->Data[i][j] = 0;

    for (unsigned int m = 0; m < AudNum; m++)
        for (unsigned int j = 0; j < AUDIO[m].SamplesPerChannel; j++)
            for (unsigned int i = 0; i < ptr->ChannelNr; i++)
                ptr->Data[i][j] += AUDIO[m].Data[i][j];

    free(AUDIO);

    return ptr;
}