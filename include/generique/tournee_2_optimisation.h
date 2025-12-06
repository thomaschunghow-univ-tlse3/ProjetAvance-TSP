/*
 * tournee_2_optimisation.h
 *
 * Algorithme de 2-optimisation.
 */

#ifndef TOURNEE_2_OPTIMISATION_H
#define TOURNEE_2_OPTIMISATION_H

#include "structure_matrice.h"
#include "structure_permutation.h"

void tournee_plus_proche_voisin(MatriceDistance, Permutation permutation_resultat);

void tournee_marche_aleatoire(MatriceDistance, Permutation permutation_resultat);

void tournee_2_optimisation(MatriceDistance, Permutation permutation_courante, Permutation permutation_resultat);

void tournee_2_optimisation_plus_proche_voisin(MatriceDistance, Permutation permutation_courante, Permutation permutation_resultat);

void tournee_2_optimisation_marche_aleatoire(MatriceDistance, Permutation permutation_courante, Permutation permutation_resultat);

#endif // TOURNEE_2_OPTIMISATION_H
