#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "commandtreat.h"

void PreSet(arguments_t *ARGUMENTS)
{
    ARGUMENTS->OUTPUT = stdout;
    ARGUMENTS->NumInputs = 1;
    ARGUMENTS->Revert = 0;
    ARGUMENTS->AutoVol = 0;
    ARGUMENTS->Volume = 1.0;
    ARGUMENTS->Aten = 0.5;
    ARGUMENTS->Delay = 1000;
    ARGUMENTS->Wide = 1.0;
}

void SetInputs(arguments_t *ARGUMENTS)
{
    ARGUMENTS->INPUTS = malloc(ARGUMENTS->NumInputs * sizeof(FILE*));
    ARGUMENTS->INPUTS[0] = stdin;
}

void TreatArgs(int argc, char *argv[], char *POSSIBLE_ARGS, arguments_t *ARGUMENTS, float *Setting1, float *Setting2)
{

    for (unsigned int i = 1; i <= argc - 1; i += 2)
    {
        if (argv[i][0] == '-')
            switch (argv[i][1])
            {
                case 'i':
                {
                    for (unsigned int k = 0; k < ARGUMENTS->NumInputs; k++)
                        ARGUMENTS->INPUTS[k] = fopen(argv[i+1], "r");
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