/*
 * structure_permutation.h
 *
 * Définitions et opérations sur les permutations.
 *
 * Remarque : les permutations sont initialisées dans l’ordre canonique,
 * puis parcourues dans l’ordre lexical, en fixant le premier indice.
 * C'est-à-dire, on calcule les (n-1)! permutations, et non pas les n! permutations,
 * car comparer toutes les tournées revient à comparer toutes les tournées qui partent du même point.
 */

#ifndef STRUCTURE_PERMUTATION_H
#define STRUCTURE_PERMUTATION_H

#include "structure_matrice.h"

#include <stdbool.h>

typedef struct permutation *Permutation;

Permutation permutation_creer(size_t nombre_indices);
void permutation_supprimer(Permutation *);

bool permutation_avancer(Permutation);

size_t permutation_obtenir_taille(Permutation);

size_t permutation_obtenir_indice(Permutation, size_t indice);

distance permutation_calculer_distance_totale(Permutation, MatriceDistance);
distance permutation_calculer_distance_totale_rapide(Permutation, MatriceDistance, distance longueur_minimale);

void permutation_copier(Permutation destination, Permutation source);

#endif // STRUCTURE_PERMUTATION_H
