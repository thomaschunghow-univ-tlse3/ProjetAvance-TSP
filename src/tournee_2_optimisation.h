/*
 * tournee_2_optimisation.h
 *
 * Algorithme de 2-optimisation.
 */

#ifndef TOURNEE_2_OPTIMISATION_H
#define TOURNEE_2_OPTIMISATION_H

#include "tournee_canonique.h"
#include "affichage.h"

typedef int (*compar)(const void *,const void *);

Resultat tournee_plus_proche_voisin(MatriceDistance);

size_t donner_nombre_aleatoire(size_t borne_inf, size_t borne_sup);

Resultat tournee_marche_aleatoire(MatriceDistance);

Resultat tournee_2_optimisation_plus_proche_voisin(MatriceDistance);

Resultat tournee_2_optimisation_marche_aleatoire(MatriceDistance);

void recherche_croisement(MatriceDistance matrice);

#endif // TOURNEE_2_OPTIMISATION_H