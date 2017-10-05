#ifndef __COMMON__
#define __COMMON__

typedef struct arguments
    {
        FILE *INPUT;
        FILE *OUTPUT;
        char Revert;
        char AutoVol;
        char Cat;
        char Mix;
        float Volume;
        float Delay;
        float Aten;
        float Wide;

    } arguments_t;

typedef struct audio
    {
        char *ChunkID[5];
        unsigned int *ChunkSize;
        char *Format[5];
        char *SubChunk1ID[5];
        unsigned int *SubChunk1Size;
        unsigned short *AudioFormat;
        unsigned short *ChannelNr;
        unsigned int *SampleRate;
        unsigned int *ByteRate;
        unsigned short *BlockAlign;
        unsigned short *BitsPerSample;
        char *SubChunk2ID[5];
        unsigned int *SubChunk2Size;
        signed short **Data;
        arguments_t *ARGUMENTS;

    } audio_t;

#endif