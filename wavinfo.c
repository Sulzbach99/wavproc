#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"

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

    printf("riff tag       : \"%s\"\n", AUDIO.ChunkID);
    printf("riff size      : %i\n", AUDIO.ChunkSize);
    printf("wave tag       : \"%s\"\n", AUDIO.Format);
    printf("form tag       : \"%s\"\n", AUDIO.SubChunk1ID);
    printf("fmt_size       : %i\n", AUDIO.SubChunk1Size);
    printf("audio_format   : %i\n", AUDIO.AudioFormat);
    printf("num_channels   : %i\n", AUDIO.ChannelNr);
    printf("sample_rate    : %i\n", AUDIO.SampleRate);
    printf("byte_rate      : %i\n", AUDIO.ByteRate);
    printf("block_align    : %i\n", AUDIO.BlockAlign);
    printf("bits_per_sample: %i\n", AUDIO.BitsPerSample);
    printf("data tag       : \"%s\"\n", AUDIO.SubChunk2ID);
    printf("data size      : %i\n", AUDIO.SubChunk2Size);
    printf("samples/channel: %i\n", AUDIO.SubChunk2Size / AUDIO.BlockAlign);

    exit(1);
}