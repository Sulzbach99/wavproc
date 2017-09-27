#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acesso.h"

// TODO: Verificar se o arquivo é compatível
signed char LoadWAV(audio_t WAV)
{
    fread(WAV.ChunkID, 4, 1, stdin);
    fread(&WAV.ChunkSize, 4, 1, stdin);
    fread(WAV.Format, 4, 1, stdin);
    fread(WAV.SubChunk1ID, 4, 1, stdin);
    fread(&WAV.SubChunk1Size, 4, 1, stdin);
    fread(&WAV.AudioFormat, 2, 1, stdin);
    fread(&WAV.ChannelNr, 2, 1, stdin);
    fread(&WAV.SampleRate, 4, 1, stdin);
    fread(&WAV.ByteRate, 4, 1, stdin);
    fread(&WAV.BlockAlign, 2, 1, stdin);
    fread(&WAV.BitsPerSample, 2, 1, stdin);
    fread(WAV.SubChunk2ID, 4, 1, stdin);
    fread(&WAV.SubChunk2Size, 4, 1, stdin);

    WAV.Data = malloc(WAV.SubChunk2Size);

    return 1;
}