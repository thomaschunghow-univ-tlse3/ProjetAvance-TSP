/*
 * tournee_genetique.h
 *
 * Algorithme génétique.
 */

#ifndef TOURNEE_GENETIQUE_H
#define TOURNEE_GENETIQUE_H

#include "structure_matrice.h"
#include "structure_permutation.h"

Permutation tournee_genetique_light(MatriceDistance, size_t nombre_individus, size_t nombre_generations, double taux_mutation, size_t taille_tournoi);

Permutation tournee_genetique_dpx(MatriceDistance, size_t nombre_individus, size_t nombre_generations, double taux_mutation);

#endif // TOURNEE_GENETIQUE_H
