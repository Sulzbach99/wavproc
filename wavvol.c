#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"

void Mult(signed short *v, unsigned int a, unsigned int b)
{
    for (unsigned int i = a; i <= b; i++)
        v[i] *= Volume;
}

int main(int argc, char *argv[])
{
    if (!TreatArgs(argc, argv))
    {
        fprintf(stderr, "Could not understand argument(s)\n");
        fprintf(stderr, "e.g. wavinfo -i [input] -o [output]\n");
        exit(0);
    }

    if (!LoadAudio())
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    for (unsigned int k = 0; k < AUDIO.ChannelNr; k++)
        Mult(AUDIO.Data[k], 0, (AUDIO.SubChunk2Size / AUDIO.BlockAlign) - 1);

    fwrite(AUDIO.ChunkID, sizeof(char), 4, OUTPUT);
    fwrite(&AUDIO.ChunkSize, sizeof(int), 1, OUTPUT);
    fwrite(AUDIO.Format, sizeof(char), 4, OUTPUT);
    fwrite(AUDIO.SubChunk1ID, sizeof(char), 4, OUTPUT);
    fwrite(&AUDIO.SubChunk1Size, sizeof(int), 1, OUTPUT);
    fwrite(&AUDIO.AudioFormat, sizeof(short), 1, OUTPUT);
    fwrite(&AUDIO.ChannelNr, sizeof(short), 1, OUTPUT);
    fwrite(&AUDIO.SampleRate, sizeof(int), 1, OUTPUT);
    fwrite(&AUDIO.ByteRate, sizeof(int), 1, OUTPUT);
    fwrite(&AUDIO.BlockAlign, sizeof(short), 1, OUTPUT);
    fwrite(&AUDIO.BitsPerSample, sizeof(short), 1, OUTPUT);
    fwrite(AUDIO.SubChunk2ID, sizeof(char), 4, OUTPUT);
    fwrite(&AUDIO.SubChunk2Size, sizeof(int), 1, OUTPUT);
    for (unsigned int j = 0; j < AUDIO.SubChunk2Size / AUDIO.BlockAlign; j++)
        for (unsigned int i = 0; i < AUDIO.ChannelNr; i++)
            fwrite(&AUDIO.Data[i][j], sizeof(short), 1, OUTPUT);
    
    fclose(OUTPUT);
    exit(1);
}