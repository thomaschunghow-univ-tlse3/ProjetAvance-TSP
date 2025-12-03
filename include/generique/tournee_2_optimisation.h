/*
 * tournee_2_optimisation.h
 *
 * Algorithme de 2-optimisation.
 */

#ifndef TOURNEE_2_OPTIMISATION_H
#define TOURNEE_2_OPTIMISATION_H

#include "structure_matrice.h"
#include "structure_permutation.h"

Permutation tournee_plus_proche_voisin(MatriceDistance);

Permutation tournee_marche_aleatoire(MatriceDistance);

void tournee_2_optimisation(MatriceDistance, Permutation);

Permutation tournee_2_optimisation_plus_proche_voisin(MatriceDistance);

Permutation tournee_2_optimisation_marche_aleatoire(MatriceDistance);

#endif // TOURNEE_2_OPTIMISATION_H
