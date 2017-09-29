#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "commandtreat.h"

char TreatArgs(int argc, char *argv[])
{
    strcpy(ARGS.Input, "stdin");
    strcpy(ARGS.Output, "stdout");

    for (unsigned int i = 1; i <= argc - 1; i += 2)
        if (!strcmp(argv[i], "-i"))
            strcpy(ARGS.Input, argv[i+1]);
        else if (!strcmp(argv[i], "-o"))
            strcpy(ARGS.Output, argv[i+1]);
        else
            return 0;

    return 1;
}