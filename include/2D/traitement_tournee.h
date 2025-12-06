/*
 * traitement_tournee.h
 *
 * Outil de traitement de tous les algorithmes de tournée.
 */

#ifndef TRAITEMENT_TOURNEE_H
#define TRAITEMENT_TOURNEE_H

#include "options.h"
#include "structure_matrice.h"
#include "structure_permutation.h"

typedef Permutation (*AlgorithmeTournee)(MatriceDistance);

void tournee_traiter_methode(FILE *sortie, Arguments, MatriceDistance);

#endif // TRAITEMENT_TOURNEE_H
