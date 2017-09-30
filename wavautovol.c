#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

int main(int argc, char *argv[])
{
    if (!TreatArgs(argc, argv))
    {
        fprintf(stderr, "Could not understand argument(s)\n");
        exit(0);
    }

    if (!LoadAudio())
    {
        fprintf(stderr, "File is unsupported or corrupted\n");
        exit(0);
    }

    AutoVol();

    Write();

    exit(1);
}