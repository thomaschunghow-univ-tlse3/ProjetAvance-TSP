/*
 * lecture_donnees.h
 *
 * Outil de lecture de la spécification d'un fichier TSP,
 * et de lecture des coordonnées des points et de leur stockage dans un tableau.
 */

#ifndef LECTURE_DONNEES_H
#define LECTURE_DONNEES_H

#include "structure.h"

#include <stdio.h>

#define TAILLE_SPECIFICATION_MAX 1000

typedef struct
{
    char nom[TAILLE_SPECIFICATION_MAX];
    char type[TAILLE_SPECIFICATION_MAX];
    char commentaire[TAILLE_SPECIFICATION_MAX];
    size_t nombre_points;
    DistanceCalculer calculer_distance;
} Specification;

Specification lecture_specification_tsp(FILE *fichier);

void lecture_points_tsp(FILE *fichier, TableauPoint);

#endif // LECTURE_DONNEES_H
