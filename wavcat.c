#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define OPTS "io~~"

int main(int argc, char *argv[])
{
    audio_t *AUDIO;
    unsigned short AudNum = 0;

    for (unsigned int i = 1; i < argc - 1; i++)
        if (strstr(argv[i], ".wav"))
            AudNum++;

    AUDIO = Malloc(AudNum * sizeof(audio_t));

    strcpy(argv[0], "-i");

    for (unsigned int j = 1; j <= AudNum; j++)
    {
        AUDIO[j-1].INPUT = stdin;
        AUDIO[j-1].OUTPUT = stdout;

        strcpy(argv[1], argv[j]);
        TreatArgs(argc, argv, OPTS, &AUDIO[j-1].INPUT, &AUDIO[j-1].OUTPUT, NULL, NULL);
    }

    for (unsigned int k = 0; k < AudNum; k++)
        LoadAudio(&AUDIO[k]);

    AUDIO = CatAudios(AUDIO, AudNum);
    AUDIO->INPUT = stdin;
    AUDIO->OUTPUT = stdout;
    TreatArgs(argc, argv, OPTS, &AUDIO->INPUT, &AUDIO->OUTPUT, NULL, NULL);

    Write(AUDIO);

    exit(EXIT_SUCCESS);
}