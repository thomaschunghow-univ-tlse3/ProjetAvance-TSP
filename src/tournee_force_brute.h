/*
 *force_brute.h
 */

#ifndef TOURNEE_FORCE_BRUTE_H
#define TOURNEE_FORCE_BRUTE_H

#include "structures_de_donnees.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool permutation_suivante(Permutation);
distance brute_force(MatriceDistances matrice);

void traitement_bf(FILE *sortie, MatriceDistances matrice);

#endif // TOURNEE_FORCE_BRUTE_H