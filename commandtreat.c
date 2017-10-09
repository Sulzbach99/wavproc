#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"

void TreatArgs(int argc, char *argv[], char *POSSIBLE_ARGS, arguments_t *ARGUMENTS, float *Setting1, float *Setting2)
{
    ARGUMENTS->INPUT = stdout;
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