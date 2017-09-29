#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "audiotreat.h"

void Revert(signed short *v, unsigned int a, unsigned int b)
{
    short aux;

    while (a < b)
    {
        aux = v[a];
        v[a] = v[b];
        v[b] = aux;

        a++;
        b--;
    }
}