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
    audio_t *AUDIO = NULL;
    unsigned int AudNum = 0;

    for (unsigned int i = 1; i < argc; i++)
        if (strstr(".wav", argv[i]))
            AudNum++;

    AllocAudio(AUDIO, AudNum);

    strcpy(argv[0], "-i");

    for (unsigned int j = 1; j <= AudNum; j++)
    {
        strcpy(argv[1], argv[j]);
        TreatArgs(argc, argv, POSSIBLE_ARGS, &AUDIO->ARGUMENTS, NULL, NULL);
    }

    for (unsigned int k = 0; k < AudNum; k++)
        if (!LoadAudio(&AUDIO[k]))
        {
            fprintf(stderr, "File is unsupported or corrupted\n");
            exit(0);
        }

    AUDIO = CatAudios(AUDIO, AudNum);

    Write(AUDIO);

    exit(1);
}