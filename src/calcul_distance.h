/*
 *
 * Ce module fournit les différentes méthodes de calcul de distance.
 */

#ifndef CALCUL_DISTANCE_H
#define CALCUL_DISTANCE_H

#include "structure_permutation.h"

typedef distance (*FonctionCalcul)(Point, Point);

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
extern FonctionCalcul liste_fonctions_calcul[];

#endif // CALCUL_DISTANCE_H
