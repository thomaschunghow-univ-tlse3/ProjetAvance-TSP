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

#endif // TOURNEE_2_OPTIMISATION_H