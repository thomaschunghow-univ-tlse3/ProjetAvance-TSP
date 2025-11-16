/*
 * traitement_tournee.h
 *
 * Outil de traitement de tous les algorithmes de tournée.
 */

#ifndef TRAITEMENT_TOURNEE_H
#define TRAITEMENT_TOURNEE_H

#include "structure_permutation.h"
#include "options.h"

typedef struct
{
    Permutation permutation;
    distance longueur;
} Resultat;

typedef Resultat (*AlgorithmeTournee)(MatriceDistance);

void tournee_traitement(FILE *sortie, Options, MatriceDistance);

#endif // TRAITEMENT_TOURNEE_H
