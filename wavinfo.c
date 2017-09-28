#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "access.h"

int main()
{
    LoadAudio();

    printf("riff tag       : \"%s\"\n", WAV.ChunkID);
    printf("riff size      : %i\n", WAV.ChunkSize);
    printf("wave tag       : \"%s\"\n", WAV.Format);
    printf("form tag       : \"%s\"\n", WAV.SubChunk1ID);
    printf("fmt_size       : %i\n", WAV.SubChunk1Size);
    printf("audio_format   : %i\n", WAV.AudioFormat);
    printf("num_channels   : %i\n", WAV.ChannelNr);
    printf("sample_rate    : %i\n", WAV.SampleRate);
    printf("byte_rate      : %i\n", WAV.ByteRate);
    printf("block_align    : %i\n", WAV.BlockAlign);
    printf("bits_per_sample: %i\n", WAV.BitsPerSample);
    printf("data tag       : \"%s\"\n", WAV.SubChunk2ID);
    printf("data size      : %i\n", WAV.SubChunk2Size);
    printf("samples/channel: %i\n", WAV.SubChunk2Size / WAV.BlockAlign);

    exit(1);
}