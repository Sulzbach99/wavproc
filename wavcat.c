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
    arguments_t *ARGUMENTS;
    unsigned int cont;

    for (unsigned int k = 2; argv[k][0] != '-'; k++)
        cont = k - 2;

    AUDIO = malloc(cont * sizeof(audio_t));
    ARGUMENTS = malloc(cont * sizeof(arguments_t));

    for (unsigned int l = 0; l < cont; l++)
        PreSet(&ARGUMENTS[l]);

    for (unsigned int m = 0; m < cont; m++)
    {
        TreatArgs(argc, argv, POSSIBLE_ARGS, &ARGUMENTS[m], NULL, NULL);
        for (unsigned int n = 2; n < --argc; n++)
            strcpy(argv[n], argv[n+1]);
    }

    for (unsigned int o; o < cont; o++)
        if (!LoadAudio(&AUDIO[o], &ARGUMENTS[o]))
        {
            fprintf(stderr, "File is unsupported or corrupted\n");
            exit(0);
        }

    for (unsigned int p; p < cont; p++)
        TreatAudio(&AUDIO[p], &ARGUMENTS[p]);

    for (unsigned int q; q < cont; q++)
        Write(&AUDIO[q], &ARGUMENTS[q]);

    exit(1);
}