/*
 *
 * Ce module fournit les différentes méthodes de calcul de distance.
 */

#ifndef STRUCTURES_CALCULS_DISTANCES_H
#define STRUCTURES_CALCULS_DISTANCES_H

#include "structures_permutations.h"

typedef enum
{
    EUC_2D,
    GEO,
    ATT
} TypeDistance;

distance calculer_distance_euclidienne(Point A, Point B);
distance calculer_distance_geographique(Point A, Point B);
distance calculer_distance_euclidienne_modifiee(Point A, Point B);

/* Liste qui contient les trois pointeurs vers les trois fonctions de calcul de distances,
 * indexés selon l'ordre de l'énumération TypeDistance. */
extern FonctionCalculDistance liste_fonctions_calcul[];

#endif // STRUCTURES_CALCULS_DISTANCES_H
