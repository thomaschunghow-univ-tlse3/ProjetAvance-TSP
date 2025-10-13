/*
 * traitement_lecture_donnees.h
 *
 * Ce module permet :
 * - La lecture de la spécification d'un fichier TSP,
 * - La lecture des coordonnées des points et leur stockage dans un tableau dynamique.
 */

#ifndef TRAITEMENT_LECTURE_DONNEES_H
#define TRAITEMENT_LECTURE_DONNEES_H

#include "structures_de_donnees.h"

#include <stdio.h>

#define TAILLE_CHAMP_MAX 100

typedef struct
{
    char nom[TAILLE_CHAMP_MAX];
    char type[TAILLE_CHAMP_MAX];
    char commentaire[TAILLE_CHAMP_MAX];
    size_t nombre_points;
    FonctionCalculDistance calculer_distance;
} Specification;

Specification lire_specification_tsp(FILE *fichier);

void lire_points_tsp(FILE *fichier, TableauPoints);

#endif // TRAITEMENT_LECTURE_DONNEES_H
