/*
 * lecture_tsp.h
 *
 * Outil de lecture de la spécification d'un fichier TSP,
 * et de lecture des coordonnées des points et de leur stockage dans un tableau.
 */

#ifndef LECTURE_TSP_H
#define LECTURE_TSP_H

#include "structure.h"

#include <stdio.h>

#define LECTURE_TSP_TAILLE_MAX 100

typedef struct
{
    char nom[LECTURE_TSP_TAILLE_MAX];
    char type[LECTURE_TSP_TAILLE_MAX];
    char commentaire[LECTURE_TSP_TAILLE_MAX];
    size_t nombre_points;
    DistanceCalculer distance_calculer;
    DistanceAdditionner distance_additionner;
    DistanceSoustraire distance_soustraire;
    DistanceComparer distance_comparer;
} Specification;

Specification lecture_tsp_lire_specification(FILE *fichier);

void lecture_tsp_lire_points(FILE *fichier, MatriceDistance);

#endif // LECTURE_TSP_H
