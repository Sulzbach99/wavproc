#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"

#define POSSIBLE_ARGS "ioxx"

int main(int argc, char *argv[])
{
    audio_t AUDIO;
    arguments_t ARGUMENTS;

    if (!TreatArgs(argc, argv, POSSIBLE_ARGS, &ARGUMENTS, NULL))
    {
        fprintf(stderr, "Could not understand argument(s)\n");
        exit(0);
    }

    if (!LoadAudio(&AUDIO, &ARGUMENTS))
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    fprintf(ARGUMENTS.OUTPUT, "riff tag       : \"%s\"\n", AUDIO.ChunkID);
    fprintf(ARGUMENTS.OUTPUT, "riff size      : %i\n", AUDIO.ChunkSize);
    fprintf(ARGUMENTS.OUTPUT, "wave tag       : \"%s\"\n", AUDIO.Format);
    fprintf(ARGUMENTS.OUTPUT, "form tag       : \"%s\"\n", AUDIO.SubChunk1ID);
    fprintf(ARGUMENTS.OUTPUT, "fmt_size       : %i\n", AUDIO.SubChunk1Size);
    fprintf(ARGUMENTS.OUTPUT, "audio_format   : %i\n", AUDIO.AudioFormat);
    fprintf(ARGUMENTS.OUTPUT, "num_channels   : %i\n", AUDIO.ChannelNr);
    fprintf(ARGUMENTS.OUTPUT, "sample_rate    : %i\n", AUDIO.SampleRate);
    fprintf(ARGUMENTS.OUTPUT, "byte_rate      : %i\n", AUDIO.ByteRate);
    fprintf(ARGUMENTS.OUTPUT, "block_align    : %i\n", AUDIO.BlockAlign);
    fprintf(ARGUMENTS.OUTPUT, "bits_per_sample: %i\n", AUDIO.BitsPerSample);
    fprintf(ARGUMENTS.OUTPUT, "data tag       : \"%s\"\n", AUDIO.SubChunk2ID);
    fprintf(ARGUMENTS.OUTPUT, "data size      : %i\n", AUDIO.SubChunk2Size);
    fprintf(ARGUMENTS.OUTPUT, "samples/channel: %i\n", AUDIO.SubChunk2Size / AUDIO.BlockAlign);

    fclose(ARGUMENTS.OUTPUT);
    exit(1);
}