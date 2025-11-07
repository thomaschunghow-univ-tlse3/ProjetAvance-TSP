/*
 * calcul_distance.h
 *
 * Fonctions de calcul de distance.
 */

#ifndef CALCUL_DISTANCE_H
#define CALCUL_DISTANCE_H

#include "structure_permutation.h"
#include <stddef.h>

typedef distance (*FonctionCalcul)(Point, Point);

typedef enum
{
    EUC_2D,
    GEO,
    ATT
} TypeDistance;


size_t calculer_factorielle(size_t);

size_t factorielle(size_t);

size_t calculer_factorielle(size_t);

distance calculer_distance_euclidienne(Point A, Point B);
distance calculer_distance_geographique(Point A, Point B);
distance calculer_distance_euclidienne_modifiee(Point A, Point B);

#endif // CALCUL_DISTANCE_H
