#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "commandtreat.h"

void TreatArgs(int argc, char *argv[])
{
    for (unsigned int i = 1; i <= argc - 1; i += 2)
        if (!strcmp(argv[i], "-i"))
            strcpy(ARGS.Input, argv[i+1]);
}