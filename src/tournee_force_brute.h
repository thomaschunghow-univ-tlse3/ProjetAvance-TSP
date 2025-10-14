/*
 */

#ifndef TOURNEE_FORCE_BRUTE_H
#define TOURNEE_FORCE_BRUTE_H

#include "structures_permutations.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

bool permutation_suivante(Permutation);
Permutation brute_force(MatriceDistances matrice);

Resultat calcul_tournee_force_brute(MatriceDistances matrice);

#endif // TOURNEE_FORCE_BRUTE_H