#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"

static int Comp(const void *a, const void *b)
{
    char *a2 = (char *)a;
    char *b2 = (char *)b;

    if (*a2 > *b2)
        return 1;

    if (*a2 < *b2)
        return -1;

    return 0;
}

void TreatArgs(int argc, char *argv[], char *OPTS, arguments_t *ARGUMENTS, float *Setting1, float *Setting2)
{
    ARGUMENTS->INPUT = stdin;
    ARGUMENTS->OUTPUT = stdout;
    ARGUMENTS->Revert = 0;
    ARGUMENTS->AutoVol = 0;
    ARGUMENTS->Volume = 1.0;
    ARGUMENTS->Aten = 0.5;
    ARGUMENTS->Delay = 0;
    ARGUMENTS->Wide = 1.0;

    for (unsigned int i = 0; i <= argc - 1; i++)
    {
        if (argv[i][0] == '-')
        {
            if (!bsearch(&argv[i][1], OPTS, 4, 1, Comp))
            {
                fprintf(stderr, "argument error\n");
                exit(EXIT_FAILURE);
            }

            switch (argv[i][1])
            {
                case 'i':
                {
                    ARGUMENTS->INPUT = fopen(argv[i+1], "r");
                    break;
                }
                case 'o':
                {
                    ARGUMENTS->OUTPUT = fopen(argv[i+1], "w");
                    break;
                }
                case 'l':
                {
                    *Setting1 = atof(argv[i+1]);
                    break;
                }
                case 't':
                {
                    *Setting2 = atof(argv[i+1]);
                    break;
                }
            }
        }
    }
}