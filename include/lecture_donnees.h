/*
 * lecture_donnees.h
 *
 * Outil de lecture de la spécification d'un fichier TSP,
 * et de lecture des coordonnées des points et de leur stockage dans un tableau.
 */

#ifndef LECTURE_DONNEES_H
#define LECTURE_DONNEES_H

#include "structure_permutation.h"

#include <stdio.h>

#define TAILLE_CHAMP_MAX 1000

typedef struct
{
    char nom[TAILLE_CHAMP_MAX];
    char type[TAILLE_CHAMP_MAX];
    char commentaire[TAILLE_CHAMP_MAX];
    size_t nombre_points;
    FonctionCalcul calculer_distance;
} Specification;

Specification lire_specification_tsp(FILE *fichier);

void lire_points_tsp(FILE *fichier, TableauPoint);

#endif // LECTURE_DONNEES_H
