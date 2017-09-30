#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "commandtreat.h"

char TreatArgs(int argc, char *argv[])
{
    INPUT = stdin;
    OUTPUT = stdout;
    Volume = 1.0;

    for (unsigned int i = 1; i <= argc - 1; i += 2)
        if (!strcmp(argv[i], "-i"))
            INPUT = fopen(argv[i+1], "r");
        else if (!strcmp(argv[i], "-o"))
            OUTPUT = fopen(argv[i+1], "w");
        else if (!strcmp(argv[i], "-l"))
            Volume = atof(argv[i+1]);
        else if (!strcmp(argv[i], "-t"))
            Delay = atof(argv[i+1]);
        else
            return 0;

    return 1;
}