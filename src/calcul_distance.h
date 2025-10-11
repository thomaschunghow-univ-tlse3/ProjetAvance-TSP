/*
 * calcul_distance.h
 *
 * Ce module fournit les différentes méthodes de calcul de distance.
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

distance calculer_distance_euclidienne(Point A, Point B);
distance calculer_distance_geographique(Point A, Point B);
distance calculer_distance_euclidienne_modifiee(Point A, Point B);

/* Liste qui contient les trois pointeurs vers les trois fonctions de calcul de distances,
 * indexés selon l'ordre de l'énumération TypeDistance. */
extern calculer_distance liste_fonctions_calcul[];

#endif // CALCUL_DISTANCE_H
