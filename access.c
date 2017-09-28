#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "access.h"

void LoadAudio()
{
    FILE *INPUT;
    
    INPUT = fopen(ARGS.Input, "r");

    // Leitura do cabeçalho do arquivo de áudio:
    fread(AUDIO.ChunkID, sizeof(char), 4, INPUT);
    fread(&AUDIO.ChunkSize, sizeof(int), 1, INPUT);
    fread(AUDIO.Format, sizeof(char), 4, INPUT);
    fread(AUDIO.SubChunk1ID, sizeof(char), 4, INPUT);
    fread(&AUDIO.SubChunk1Size, sizeof(int), 1, INPUT);
    fread(&AUDIO.AudioFormat, sizeof(short), 1, INPUT);
    fread(&AUDIO.ChannelNr, sizeof(short), 1, INPUT);
    fread(&AUDIO.SampleRate, sizeof(int), 1, INPUT);
    fread(&AUDIO.ByteRate, sizeof(int), 1, INPUT);
    fread(&AUDIO.BlockAlign, sizeof(short), 1, INPUT);
    fread(&AUDIO.BitsPerSample, sizeof(short), 1, INPUT);
    fread(AUDIO.SubChunk2ID, sizeof(char), 4, INPUT);
    fread(&AUDIO.SubChunk2Size, sizeof(int), 1, INPUT);

    AUDIO.ChunkID[4] = AUDIO.Format[4] = AUDIO.SubChunk1ID[4] = AUDIO.SubChunk2ID[4] = 0;

    // Alocação dinâmica de uma matriz onde cada linha é um canal e cada coluna é uma amostra:
    AUDIO.Data = malloc(AUDIO.ChannelNr * sizeof(int*));
    for (unsigned int k = 0; k < AUDIO.ChannelNr; k++)
        AUDIO.Data[k] = malloc(AUDIO.SubChunk2Size / AUDIO.ChannelNr);

    // Leitura de cada elemento da matriz:
    for (unsigned int j = 0; j < AUDIO.SubChunk2Size / AUDIO.BlockAlign; j++)
        for (unsigned int i = 0; i < AUDIO.ChannelNr; i++)
            fread(&AUDIO.Data[i][j], sizeof(int), 1, INPUT);

    fclose(INPUT);
}