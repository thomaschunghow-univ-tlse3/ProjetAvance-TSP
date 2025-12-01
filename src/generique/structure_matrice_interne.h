/*
 * structure_matrice_interne.h
 */

#ifndef STRUCTURE_MATRICE_INTERNE_H
#define STRUCTURE_MATRICE_INTERNE_H

#include "structure_matrice.h"

#include <stddef.h>

struct tableau_point
{
    size_t nombre_points;
    size_t taille_point;

    char *points;
    /* On utilise le type char pour pouvoir faire de l'arithmétique de pointeurs,
     * car void n'a pas de taille. */
};

struct tableau_distance
{
    size_t nombre_distances;
    size_t taille_distance;

    DistanceCalculer distance_calculer;
    DistanceAdditionner distance_additionner;
    DistanceSoustraire distance_soustraire;
    DistanceComparer distance_comparer;

    char *distances;
    /* On utilise le type char pour pouvoir faire de l'arithmétique de pointeurs,
     * car void n'a pas de taille. */
};

struct matrice_distance
{
    struct tableau_point tableau_point;
    struct tableau_distance tableau_distance;
};

size_t matrice_calculer_indice(size_t ligne, size_t colonne);

#endif // STRUCTURE_MATRICE_INTERNE_H
