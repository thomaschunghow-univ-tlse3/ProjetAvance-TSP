/*
 *
 */

#ifndef LECTURE_DONNEE_H
#define LECTURE_DONNEE_H

#include "structures_de_donnees.h"
#include "calcul_distance.h"

#include <stdio.h>

#define TAILLE_LIGNE_MAX 100
#define TAILLE_CHAMP_MAX 100

typedef struct
{
    char nom[TAILLE_CHAMP_MAX];
    char type[TAILLE_CHAMP_MAX];
    char commentaire[TAILLE_CHAMP_MAX];
    size_t nombre_points;
    TypeDistance type_distance;
} Specification;

Specification lire_specification_tsp(FILE *fichier);

void lire_points_tsp(FILE *fichier, TableauPoints);

#endif // LECTURE_DONNEE_H
