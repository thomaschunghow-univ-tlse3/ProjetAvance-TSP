/*
 *
 * Ce module fournit :
 *  - Les types de coordonnées et de distances,
 *  - Les tableaux dynamiques de points et de distances (types abstraits),
 *  - Les demi-matrices de distances (type abstrait),
 *  - Les fonctions de création, accès, calcul et suppression de ces structures.
 */

#ifndef STRUCTURES_PERMUTATIONS_H
#define STRUCTURES_PERMUTATIONS_H

#include "structures_matrices.h"

#include <stddef.h>

typedef struct permutation *Permutation;

struct permutation
{
    size_t nombre_indices;
    size_t *indices;
};

/* Définition d'une permutation. */
typedef struct permutation *Permutation;

/* Le tableau est créé et initialisé avec la première permutation
 * de l'ordre lexical, i.e l'ordre canonique de 1 à n. */
Permutation creer_permutation(size_t nombre_indices);
void supprimer_permutation(Permutation *permutation);

void echanger_indices(Permutation permutation, int i, int j);

/* calcule la distance totale d'une sequence de points d'une permutation*/
distance distance_totale_permutation(Permutation, MatriceDistances);

#endif // STRUCTURES_PERMUTATIONS_H
