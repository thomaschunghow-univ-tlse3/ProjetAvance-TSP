/*
 *
 * Ce module fournit :
 *  - Les types de coordonnées et de distances,
 *  - Les tableaux dynamiques de points et de distances (types abstraits),
 *  - Les demi-matrices de distances (type abstrait),
 *  - Les fonctions de création, accès, calcul et suppression de ces structures.
 */

#ifndef STRUCTURE_PERMUTATION_H
#define STRUCTURE_PERMUTATION_H

#include "structure_matrice.h"

#include <stddef.h>
#include <stdbool.h>

/* Définition d'une permutation. */
typedef struct permutation *Permutation;

size_t nombre_indices(Permutation permutation);

size_t *tableau_indices(Permutation permutation);

// TODO : rajouter une fonction qui transforme une permutation en son tableau de points correspondant.
TableauPoint transformer_permutation_en_points(Permutation permutation);

/* Le tableau est créé et initialisé avec la première permutation
 * de l'ordre lexical, i.e l'ordre canonique de 1 à n. */
Permutation creer_permutation(size_t nombre_indices);
void supprimer_permutation(Permutation *permutation);

void echanger_indices(Permutation permutation, int i, int j);

/* calcule la distance totale d'une sequence de points d'une permutation*/
distance distance_totale_permutation(Permutation, MatriceDistance);

bool permutation_suivante(Permutation permutation);

void copier_tableau(Permutation destination, Permutation source);

#endif // STRUCTURE_PERMUTATION_H
