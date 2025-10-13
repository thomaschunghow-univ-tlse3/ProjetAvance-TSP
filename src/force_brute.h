/*
 *force_brute.h
 */
#include "structures_de_donnees.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool permutation_suivante(Permutation);
distance brute_force(MatriceDistances matrice);

void traitement_bf(FILE *sortie, MatriceDistances matrice);
