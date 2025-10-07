/*
 *
 */

#ifndef CALCUL_DISTANCE_H
#define CALCUL_DISTANCE_H

#include "structures_de_donnees.h"

typedef enum
{
    EUC_2D,
    GEO,
    ATT
} TypeDistance;

distance
calculer_distance_euclidienne(Point A, Point B);

#endif // CALCUL_DISTANCE_H
