/*
 *
 */

#ifndef CALCUL_DISTANCE_H
#define CALCUL_DISTANCE_H

#include "structures_de_donnees.h"

distance calculer_distance_euclidienne(Point A, Point B);
distance calculer_distance_geographique(Point A, Point B);
distance calculer_distance_euclidienne_modifiee(Point A, Point B);

#endif // CALCUL_DISTANCE_H
