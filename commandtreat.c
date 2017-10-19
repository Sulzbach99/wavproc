//Lucas Sulzbach
//GRR20171595
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

// Lê as opções utilizadas e define entrada, saída, e parâmetros (se houverem) para o filtro do áudio:
void TreatArgs(int argc, char *argv[], char *OPTS, FILE **INPUT, FILE **OUTPUT, float *Setting1, float *Setting2)
{

    for (unsigned int i = 0; i <= argc - 1; i++)
    {
        if (argv[i][0] == '-')
        {
            if (!bsearch(&argv[i][1], OPTS, 4, 1, Comp))
            {
                fprintf(stderr, "Opcao invalida\n");
                exit(EXIT_FAILURE);
            }

            switch (argv[i][1])
            {
                case 'i':
                {
                    *INPUT = fopen(argv[i+1], "r");
                    break;
                }
                case 'o':
                {
                    *OUTPUT = fopen(argv[i+1], "w");
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