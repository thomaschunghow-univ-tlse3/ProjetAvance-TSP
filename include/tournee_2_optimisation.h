/*
 * tournee_2_optimisation.h
 *
 * Algorithme de 2-optimisation.
 */

#ifndef TOURNEE_2_OPTIMISATION_H
#define TOURNEE_2_OPTIMISATION_H

#include "tournee_canonique.h"
#include "affichage.h"

Resultat tournee_plus_proche_voisin(MatriceDistance);

Resultat tournee_marche_aleatoire(MatriceDistance);

Resultat tournee_2_optimisation_plus_proche_voisin(MatriceDistance);

Resultat tournee_2_optimisation_marche_aleatoire(MatriceDistance);

int parcours_tableau(const void *P1, const void *P2);

int normalisation(const void *P1, const void *P2);

typedef int (*compar)(const void *, const void *);

void recherche_croisement(MatriceDistance matrice, compar comparateur);

#endif // TOURNEE_2_OPTIMISATION_H