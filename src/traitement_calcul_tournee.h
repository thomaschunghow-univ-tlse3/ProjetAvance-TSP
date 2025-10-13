/*
 */

#ifndef TRAITEMENT_CALCUL_TOURNEE_H
#define TRAITEMENT_CALCUL_TOURNEE_H

#include "structures_permutations.h"
#include "traitement_options.h"

#include <stdio.h>

typedef struct
{
    Permutation permutation;
    distance distance;
} Resultat;

typedef Resultat FonctionTraitement(MatriceDistances);

void traitement(FILE *sortie, FonctionTraitement, Options, MatriceDistances);

#endif // TRAITEMENT_CALCUL_TOURNEE_H