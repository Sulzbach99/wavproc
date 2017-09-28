#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "access.h"

void LoadAudio()
{
    // Leitura do cabeçalho do arquivo de áudio:
    fread(WAV.ChunkID, sizeof(char), 4, stdin);
    fread(&WAV.ChunkSize, sizeof(int), 1, stdin);
    fread(WAV.Format, sizeof(char), 4, stdin);
    fread(WAV.SubChunk1ID, sizeof(char), 4, stdin);
    fread(&WAV.SubChunk1Size, sizeof(int), 1, stdin);
    fread(&WAV.AudioFormat, sizeof(short), 1, stdin);
    fread(&WAV.ChannelNr, sizeof(short), 1, stdin);
    fread(&WAV.SampleRate, sizeof(int), 1, stdin);
    fread(&WAV.ByteRate, sizeof(int), 1, stdin);
    fread(&WAV.BlockAlign, sizeof(short), 1, stdin);
    fread(&WAV.BitsPerSample, sizeof(short), 1, stdin);
    fread(WAV.SubChunk2ID, sizeof(char), 4, stdin);
    fread(&WAV.SubChunk2Size, sizeof(int), 1, stdin);

    WAV.ChunkID[4] = WAV.Format[4] = WAV.SubChunk1ID[4] = WAV.SubChunk2ID[4] = 0;

    // Alocação dinâmica de uma matriz onde cada linha é um canal e cada coluna é uma amostra:
    WAV.Data = malloc(WAV.ChannelNr * sizeof(int*));
    for (unsigned int k = 0; k < WAV.ChannelNr; k++)
        WAV.Data[k] = malloc(WAV.SubChunk2Size / WAV.ChannelNr);

    // Leitura de cada elemento da matriz:
    for (unsigned int j = 0; j < WAV.SubChunk2Size / WAV.BlockAlign; j++)
        for (unsigned int i = 0; i < WAV.ChannelNr; i++)
            fread(&WAV.Data[i][j], sizeof(int), 1, stdin);
}