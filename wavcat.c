#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define POSSIBLE_ARGS "ioxx"

int main(int argc, char *argv[])
{
    audio_t *AUDIO;
    unsigned int AudNum = 0;

    for (unsigned int i = 1; i < argc - 1; i++)
        if (strstr(argv[i], ".wav"))
            AudNum++;

    AUDIO = malloc(AudNum * sizeof(audio_t));

    strcpy(argv[0], "-i");

    for (unsigned int j = 1; j <= AudNum; j++)
    {
        strcpy(argv[1], argv[j]);
        TreatArgs(argc, argv, POSSIBLE_ARGS, &AUDIO[j-1].ARGUMENTS, NULL, NULL);
    }

    for (unsigned int k = 0; k < AudNum; k++)
        if (!LoadAudio(&AUDIO[k]))
        {
            fprintf(stderr, "File is unsupported or corrupted\n");
            exit(0);
        }

    AUDIO = CatAudios(AUDIO, AudNum);
    TreatArgs(argc, argv, POSSIBLE_ARGS, &AUDIO->ARGUMENTS, NULL, NULL);

    Write(AUDIO);

    exit(1);
}