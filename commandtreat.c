#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"

static int Comp(const void *a, const void *b)
{
    char *a2 = (char *) a;
    char *b2 = (char *) b;

    if (*a2 == *b2)
        return 0;
    else
        return -1;
}

char TreatArgs(int argc, char *argv[], char *ARGS)
{
    INPUT = stdin;
    OUTPUT = stdout;
    Volume = 1.0;

    for (unsigned int i = 1; i <= argc - 1; i += 2)
    {
        if (!bsearch(&argv[i][1], ARGS, 4, sizeof(char), Comp))
            return 0;

        switch (argv[i][1])
        {
            case 'i':
            {
                INPUT = fopen(argv[i+1], "r");
                break;
            }
            case 'o':
            {
                OUTPUT = fopen(argv[i+1], "w");
                break;
            }
            case 'l':
            {
                Volume = atof(argv[i+1]);
                break;
            }
        }
    }

    return 1;
}