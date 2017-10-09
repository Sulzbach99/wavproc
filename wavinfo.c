#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"

#define POSSIBLE_ARGS "ioxx"

int main(int argc, char *argv[])
{
    audio_t AUDIO;

    TreatArgs(argc, argv, POSSIBLE_ARGS, &AUDIO.ARGUMENTS, NULL, NULL);

    LoadAudio(&AUDIO);

    fprintf(AUDIO.ARGUMENTS.OUTPUT, "riff tag       : \"%s\"\n", AUDIO.ChunkID);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "riff size      : %i\n", AUDIO.ChunkSize);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "wave tag       : \"%s\"\n", AUDIO.Format);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "form tag       : \"%s\"\n", AUDIO.SubChunk1ID);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "fmt_size       : %i\n", AUDIO.SubChunk1Size);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "audio_format   : %i\n", AUDIO.AudioFormat);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "num_channels   : %i\n", AUDIO.ChannelNr);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "sample_rate    : %i\n", AUDIO.SampleRate);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "byte_rate      : %i\n", AUDIO.ByteRate);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "block_align    : %i\n", AUDIO.BlockAlign);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "bits_per_sample: %i\n", AUDIO.BitsPerSample);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "data tag       : \"%s\"\n", AUDIO.SubChunk2ID);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "data size      : %i\n", AUDIO.SubChunk2Size);
    fprintf(AUDIO.ARGUMENTS.OUTPUT, "samples/channel: %i\n", AUDIO.SubChunk2Size / AUDIO.BlockAlign);

    fclose(AUDIO.ARGUMENTS.OUTPUT);
    exit(EXIT_SUCCESS);
}