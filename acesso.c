#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acesso.h"

signed char GenMat(signed int *ptr, unsigned int lin, unsigned int col)
{
    ptr = malloc(lin * sizeof(int*));

    ptr[0] = malloc(lin * col * sizeof(int));

    for (unsigned int i = 1; i < lin; i++)
        ptr[i] = ptr[0] + i * col;

    return 1;
}

signed char LoadAudio(audio_t aud)
{
    fread(aud.ChunkID, sizeof(char), 1, stdin);
    fread(&aud.ChunkSize, sizeof(int), 1, stdin);
    fread(aud.Format, sizeof(char), 1, stdin);
    fread(aud.SubChunk1ID, sizeof(char), 1, stdin);
    fread(&aud.SubChunk1Size, sizeof(int), 1, stdin);
    fread(&aud.AudioFormat, sizeof(short), 1, stdin);
    fread(&aud.ChannelNr, sizeof(short), 1, stdin);
    fread(&aud.SampleRate, sizeof(int), 1, stdin);
    fread(&aud.ByteRate, sizeof(int), 1, stdin);
    fread(&aud.BlockAlign, sizeof(short), 1, stdin);
    fread(&aud.BitsPerSample, sizeof(short), 1, stdin);
    fread(aud.SubChunk2ID, sizeof(char), 1, stdin);
    fread(&aud.SubChunk2Size, sizeof(int), 1, stdin);

    return 1;
}