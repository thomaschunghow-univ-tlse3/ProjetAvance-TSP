/*
 */

#ifndef TRAITEMENT_TOURNEE_H
#define TRAITEMENT_TOURNEE_H

#include "structure_permutation.h"
#include "options.h"

#include <stdio.h>

typedef struct
{
    Permutation permutation;
    distance distance;
} Resultat;

typedef Resultat (*AlgorithmeTournee)(MatriceDistance);

void calcul_tournee(FILE *sortie, Options, MatriceDistance);

#endif // TRAITEMENT_TOURNEE_H