#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "access.h"

char LoadAudio(audio_t *AUDIO)
{
    AUDIO->ChunkID[4] = AUDIO->Format[4] = AUDIO->SubChunk1ID[4] = AUDIO->SubChunk2ID[4] = 0;

    // Leitura do cabeçalho do arquivo de áudio:
    fread(AUDIO->ChunkID, sizeof(char), 4, INPUT);
    if (strcmp(AUDIO->ChunkID, "RIFF"))
        return 0;
    fread(&AUDIO->ChunkSize, sizeof(int), 1, INPUT);
    fread(AUDIO->Format, sizeof(char), 4, INPUT);
    if (strcmp(AUDIO->Format, "WAVE"))
        return 0;
    fread(AUDIO->SubChunk1ID, sizeof(char), 4, INPUT);
    fread(&AUDIO->SubChunk1Size, sizeof(int), 1, INPUT);
    fread(&AUDIO->AudioFormat, sizeof(short), 1, INPUT);
    fread(&AUDIO->ChannelNr, sizeof(short), 1, INPUT);
    fread(&AUDIO->SampleRate, sizeof(int), 1, INPUT);
    fread(&AUDIO->ByteRate, sizeof(int), 1, INPUT);
    fread(&AUDIO->BlockAlign, sizeof(short), 1, INPUT);
    fread(&AUDIO->BitsPerSample, sizeof(short), 1, INPUT);
    fread(AUDIO->SubChunk2ID, sizeof(char), 4, INPUT);
    fread(&AUDIO->SubChunk2Size, sizeof(int), 1, INPUT);

    // Alocação dinâmica de uma matriz onde cada linha é um canal e cada coluna é uma amostra:
    AUDIO->Data = malloc(AUDIO->ChannelNr * sizeof(int*));
    for (unsigned int k = 0; k < AUDIO->ChannelNr; k++)
        AUDIO->Data[k] = malloc(AUDIO->SubChunk2Size / AUDIO->ChannelNr);

    // Leitura de cada elemento da matriz:
    for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            fread(&AUDIO->Data[i][j], sizeof(short), 1, INPUT);

    fclose(INPUT);
    return 1;
}

void Write(audio_t *AUDIO)
{
    fwrite(AUDIO->ChunkID, sizeof(char), 4, OUTPUT);
    fwrite(&AUDIO->ChunkSize, sizeof(int), 1, OUTPUT);
    fwrite(AUDIO->Format, sizeof(char), 4, OUTPUT);
    fwrite(AUDIO->SubChunk1ID, sizeof(char), 4, OUTPUT);
    fwrite(&AUDIO->SubChunk1Size, sizeof(int), 1, OUTPUT);
    fwrite(&AUDIO->AudioFormat, sizeof(short), 1, OUTPUT);
    fwrite(&AUDIO->ChannelNr, sizeof(short), 1, OUTPUT);
    fwrite(&AUDIO->SampleRate, sizeof(int), 1, OUTPUT);
    fwrite(&AUDIO->ByteRate, sizeof(int), 1, OUTPUT);
    fwrite(&AUDIO->BlockAlign, sizeof(short), 1, OUTPUT);
    fwrite(&AUDIO->BitsPerSample, sizeof(short), 1, OUTPUT);
    fwrite(AUDIO->SubChunk2ID, sizeof(char), 4, OUTPUT);
    fwrite(&AUDIO->SubChunk2Size, sizeof(int), 1, OUTPUT);

    for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            fwrite(&AUDIO->Data[i][j], sizeof(short), 1, OUTPUT);
    
    fclose(OUTPUT);
}