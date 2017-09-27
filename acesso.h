typedef struct audio
    {
        const char *ChunkID;
        unsigned int ChunkSize;
        const char *Format;
        const char *SubChunk1ID;
        unsigned int SubChunk1Size;
        unsigned short AudioFormat;
        unsigned short ChannelNr;
        unsigned int SampleRate;
        unsigned int ByteRate;
        unsigned short BlockAlign;
        unsigned short BitsPerSample;
        const char *SubChunk2ID;
        unsigned int SubChunk2Size;
        signed long *Data;
    } audio_t;