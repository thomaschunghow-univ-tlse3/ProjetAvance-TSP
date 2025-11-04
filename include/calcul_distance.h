/*
 * calcul_distance.h
 *
 * Fonctions de calcul de distance.
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

<<<<<<< HEAD
<<<<<<< HEAD
size_t calculer_factorielle(size_t);
=======
size_t factorielle(size_t);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
size_t calculer_factorielle(size_t);
>>>>>>> f2faa0f (rebase)

distance calculer_distance_euclidienne(Point A, Point B);
distance calculer_distance_geographique(Point A, Point B);
distance calculer_distance_euclidienne_modifiee(Point A, Point B);

#endif // CALCUL_DISTANCE_H
