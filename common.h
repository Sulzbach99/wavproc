#ifndef __COMMON__
#define __COMMON__

typedef struct audio
    {
        signed char ChunkID[5];
        unsigned int ChunkSize;
        signed char Format[5];
        signed char SubChunk1ID[5];
        unsigned int SubChunk1Size;
        unsigned short AudioFormat;
        unsigned short ChannelNr;
        unsigned int SampleRate;
        unsigned int ByteRate;
        unsigned short BlockAlign;
        unsigned short BitsPerSample;
        signed char SubChunk2ID[5];
        unsigned int SubChunk2Size;
        signed short **Data;

    } audio_t;

audio_t WAV;

#endif