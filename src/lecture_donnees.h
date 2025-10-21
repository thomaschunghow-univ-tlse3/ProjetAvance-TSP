/*
 *
 * Ce module permet :
 * - La lecture de la spécification d'un fichier TSP,
 * - La lecture des coordonnées des points et leur stockage dans un tableau dynamique.
 */

#ifndef LECTURE_DONNEES_H
#define LECTURE_DONNEES_H

#include "structure_permutation.h"

#include <stdio.h>

#define TAILLE_CHAMP_MAX 100

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
