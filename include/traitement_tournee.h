/*
 * traitement_tournee.h
 *
 * Outil de traitement de tous les algorithmes de tournée.
 */

#ifndef TRAITEMENT_TOURNEE_H
#define TRAITEMENT_TOURNEE_H

#include "structure.h"
#include "options.h"
#include "calcul_distance.h"

typedef struct
{
    Permutation permutation;
    distance longueur;
} Resultat;

typedef Resultat (*AlgorithmeTournee)(MatriceDistance);

void tournee_traitement(FILE *sortie, Arguments, MatriceDistance);

#endif // TRAITEMENT_TOURNEE_H
