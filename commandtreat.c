#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "commandtreat.h"

char TreatArgs(int argc, char *argv[])
{
    INPUT = stdin;
    OUTPUT = stdout;

    for (unsigned int i = 1; i <= argc - 1; i += 2)
        if (!strcmp(argv[i], "-i"))
            INPUT = fopen(argv[i+1], "r");
        else if (!strcmp(argv[i], "-o"))
            OUTPUT = fopen(argv[i+1], "w");
        else
            return 0;

    return 1;
}