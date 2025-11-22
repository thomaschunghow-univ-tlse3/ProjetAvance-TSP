/*
 * calcul_distance.h
 *
 * Fonctions de calcul de distance.
 */

#ifndef CALCUL_DISTANCE_H
#define CALCUL_DISTANCE_H

#include "structure.h"

#define PI 3.14159265358979323846
#define RACINE_10 3.16227766016837952279
#define RAYON_TERRE 6378.388

typedef enum
{
    EUC_2D,
    GEO,
    ATT
} TypeDistance;

size_t calculer_factorielle(size_t);

distance calculer_distance_euclidienne(Point A, Point B);
distance calculer_distance_geographique(Point A, Point B);
distance calculer_distance_euclidienne_modifiee(Point A, Point B);

#endif // CALCUL_DISTANCE_H
