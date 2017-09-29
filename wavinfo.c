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

    fprintf(OUTPUT, "riff tag       : \"%s\"\n", AUDIO.ChunkID);
    fprintf(OUTPUT, "riff size      : %i\n", AUDIO.ChunkSize);
    fprintf(OUTPUT, "wave tag       : \"%s\"\n", AUDIO.Format);
    fprintf(OUTPUT, "form tag       : \"%s\"\n", AUDIO.SubChunk1ID);
    fprintf(OUTPUT, "fmt_size       : %i\n", AUDIO.SubChunk1Size);
    fprintf(OUTPUT, "audio_format   : %i\n", AUDIO.AudioFormat);
    fprintf(OUTPUT, "num_channels   : %i\n", AUDIO.ChannelNr);
    fprintf(OUTPUT, "sample_rate    : %i\n", AUDIO.SampleRate);
    fprintf(OUTPUT, "byte_rate      : %i\n", AUDIO.ByteRate);
    fprintf(OUTPUT, "block_align    : %i\n", AUDIO.BlockAlign);
    fprintf(OUTPUT, "bits_per_sample: %i\n", AUDIO.BitsPerSample);
    fprintf(OUTPUT, "data tag       : \"%s\"\n", AUDIO.SubChunk2ID);
    fprintf(OUTPUT, "data size      : %i\n", AUDIO.SubChunk2Size);
    fprintf(OUTPUT, "samples/channel: %i\n", AUDIO.SubChunk2Size / AUDIO.BlockAlign);

    fclose(OUTPUT);
    exit(1);
}