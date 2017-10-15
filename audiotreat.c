#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "access.h"
#include "audiotreat.h"

// Imprime informações obtidas do cabeçalho do áudio:
void GetInfo(audio_t AUDIO)
{
    fprintf(AUDIO.OUTPUT, "riff tag       : \"%s\"\n", AUDIO.ChunkID);
    fprintf(AUDIO.OUTPUT, "riff size      : %i\n", AUDIO.ChunkSize);
    fprintf(AUDIO.OUTPUT, "wave tag       : \"%s\"\n", AUDIO.Format);
    fprintf(AUDIO.OUTPUT, "form tag       : \"%s\"\n", AUDIO.SubChunk1ID);
    fprintf(AUDIO.OUTPUT, "fmt_size       : %i\n", AUDIO.SubChunk1Size);
    fprintf(AUDIO.OUTPUT, "audio_format   : %i\n", AUDIO.AudioFormat);
    fprintf(AUDIO.OUTPUT, "num_channels   : %i\n", AUDIO.ChannelNr);
    fprintf(AUDIO.OUTPUT, "sample_rate    : %i\n", AUDIO.SampleRate);
    fprintf(AUDIO.OUTPUT, "byte_rate      : %i\n", AUDIO.ByteRate);
    fprintf(AUDIO.OUTPUT, "block_align    : %i\n", AUDIO.BlockAlign);
    fprintf(AUDIO.OUTPUT, "bits_per_sample: %i\n", AUDIO.BitsPerSample);
    fprintf(AUDIO.OUTPUT, "data tag       : \"%s\"\n", AUDIO.SubChunk2ID);
    fprintf(AUDIO.OUTPUT, "data size      : %i\n", AUDIO.SubChunk2Size);
    fprintf(AUDIO.OUTPUT, "samples/channel: %i\n", AUDIO.SamplesPerChannel);

    fclose(AUDIO.OUTPUT);
}

// Reverte o áudio, por meio de um simples algoritmo iterativo:
void Rev(audio_t *AUDIO)
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

// Aumenta o volume, multiplicando cada amostra por um dado valor variável:
void Vol(audio_t *AUDIO, float Volume)
{
    for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
        for (unsigned int j = 0; j < AUDIO->SamplesPerChannel; j++)
            AUDIO->Data[i][j] *= Volume;
}

// Aumenta o volume ao máximo possível, por meio de uma regra de três:
void AutoVol(audio_t *AUDIO)
{
    signed int max = AUDIO->Data[0][0];

    for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
        for (unsigned int j = 0; j < AUDIO->SamplesPerChannel; j++)
            if (abs(AUDIO->Data[i][j]) > max)
                max = abs(AUDIO->Data[i][j]);

    Vol(AUDIO, 32767.0 / max);
}

// Efeito de eco, onde cada amostra é multiplicada por um dado valor Aten e somada
// a uma amostra posterior de acordo com um dado valor Delay:
void Echo(audio_t *AUDIO, float Aten, float Delay)
{
    unsigned int Aux = (AUDIO->SampleRate * Delay) / 1000;

    for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
        for (unsigned int j = 0; j + Aux < AUDIO->SamplesPerChannel; j++)
            AUDIO->Data[i][j+Aux] += AUDIO->Data[i][j] * Aten;

    AutoVol(AUDIO);
}

// Estéreo ampliado:
void Wide(audio_t *AUDIO, float k)
{
    signed int diff;

    for (unsigned int i = 0; i < AUDIO->SamplesPerChannel; i++)
    {
        diff = AUDIO->Data[1][i] - AUDIO->Data[0][i];

        AUDIO->Data[1][i] += k * diff;
        AUDIO->Data[0][i] -= k * diff;
    }

    AutoVol(AUDIO);
}

// Concatenação de áudios:
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

// Mixagem de áudios:
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
    ptr->SamplesPerChannel = AUDIO[0].SamplesPerChannel;

    for (unsigned int k = 1; k < AudNum; k++)
    {
        if (ptr->ChannelNr < AUDIO[k].ChannelNr)
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
            for (unsigned int i = 0; i < AUDIO[m].ChannelNr; i++)
                ptr->Data[i][j] += AUDIO[m].Data[i][j];

    free(AUDIO);

    return ptr;
}