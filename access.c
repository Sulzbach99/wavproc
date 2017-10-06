#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "access.h"

char AllocAudio(audio_t *AUDIO, char AudNum)
{
    AUDIO = malloc(AudNum * sizeof(audio_t));
    return 1;
}

char LoadAudio(audio_t *AUDIO)
{
    AUDIO->ChunkID[4] = AUDIO->Format[4] = AUDIO->SubChunk1ID[4] = AUDIO->SubChunk2ID[4] = 0;

    // Leitura do cabeçalho do arquivo de áudio:
    fread(AUDIO->ChunkID, sizeof(char), 4, AUDIO->ARGUMENTS.INPUT);
    if (strcmp(AUDIO->ChunkID, "RIFF"))
        return 0;
    fread(&AUDIO->ChunkSize, sizeof(int), 1, AUDIO->ARGUMENTS.INPUT);
    fread(AUDIO->Format, sizeof(char), 4, AUDIO->ARGUMENTS.INPUT);
    if (strcmp(AUDIO->Format, "WAVE"))
        return 0;
    fread(AUDIO->SubChunk1ID, sizeof(char), 4, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->SubChunk1Size, sizeof(int), 1, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->AudioFormat, sizeof(short), 1, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->ChannelNr, sizeof(short), 1, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->SampleRate, sizeof(int), 1, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->ByteRate, sizeof(int), 1, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->BlockAlign, sizeof(short), 1, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->BitsPerSample, sizeof(short), 1, AUDIO->ARGUMENTS.INPUT);
    fread(AUDIO->SubChunk2ID, sizeof(char), 4, AUDIO->ARGUMENTS.INPUT);
    fread(&AUDIO->SubChunk2Size, sizeof(int), 1, AUDIO->ARGUMENTS.INPUT);

    // Alocação dinâmica de uma matriz onde cada linha é um canal e cada coluna é uma amostra:
    AUDIO->Data = malloc(AUDIO->ChannelNr * sizeof(short*));
    for (unsigned int k = 0; k < AUDIO->ChannelNr; k++)
        AUDIO->Data[k] = malloc(AUDIO->SubChunk2Size / AUDIO->ChannelNr);

    // Leitura de cada elemento da matriz:
    for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            fread(&AUDIO->Data[i][j], AUDIO->BlockAlign / AUDIO->ChannelNr, 1, AUDIO->ARGUMENTS.INPUT);

    fclose(AUDIO->ARGUMENTS.INPUT);
    return 1;
}

void Write(audio_t *AUDIO)
{
    fwrite(AUDIO->ChunkID, sizeof(char), 4, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->ChunkSize, sizeof(int), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(AUDIO->Format, sizeof(char), 4, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(AUDIO->SubChunk1ID, sizeof(char), 4, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->SubChunk1Size, sizeof(int), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->AudioFormat, sizeof(short), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->ChannelNr, sizeof(short), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->SampleRate, sizeof(int), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->ByteRate, sizeof(int), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->BlockAlign, sizeof(short), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->BitsPerSample, sizeof(short), 1, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(AUDIO->SubChunk2ID, sizeof(char), 4, AUDIO->ARGUMENTS.OUTPUT);
    fwrite(&AUDIO->SubChunk2Size, sizeof(int), 1, AUDIO->ARGUMENTS.OUTPUT);

    for (unsigned int j = 0; j < AUDIO->SubChunk2Size / AUDIO->BlockAlign; j++)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            fwrite(&AUDIO->Data[i][j], sizeof(short), 1, AUDIO->ARGUMENTS.OUTPUT);
    
    fclose(AUDIO->ARGUMENTS.OUTPUT);
}