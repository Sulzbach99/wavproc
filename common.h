//Lucas Sulzbach
//GRR20171595
#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <stdlib.h>

// Struct que armazena e organiza todos os dados de um áudio:
typedef struct audio
    {
        char ChunkID[5];
        unsigned int ChunkSize;
        char Format[5];
        char SubChunk1ID[5];
        unsigned int SubChunk1Size;
        unsigned short AudioFormat;
        unsigned short ChannelNr;
        unsigned int SampleRate;
        unsigned int ByteRate;
        unsigned short BlockAlign;
        unsigned short BitsPerSample;
        char SubChunk2ID[5];
        unsigned int SubChunk2Size;
        signed int **Data;

        unsigned int SamplesPerChannel;
        FILE *INPUT;
        FILE *OUTPUT;

    } audio_t;

#endif