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

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> f2faa0f (rebase)
#define TAILLE_SPECIFICATION_MAX 1000

typedef struct
{
    char nom[TAILLE_SPECIFICATION_MAX];
    char type[TAILLE_SPECIFICATION_MAX];
    char commentaire[TAILLE_SPECIFICATION_MAX];
<<<<<<< HEAD
=======
#define TAILLE_CHAMP_MAX 1000

typedef struct
{
    char nom[TAILLE_CHAMP_MAX];
    char type[TAILLE_CHAMP_MAX];
    char commentaire[TAILLE_CHAMP_MAX];
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
>>>>>>> f2faa0f (rebase)
    size_t nombre_points;
    FonctionCalcul calculer_distance;
} Specification;

<<<<<<< HEAD
<<<<<<< HEAD
Specification lecture_specification_tsp(FILE *fichier);

void lecture_points_tsp(FILE *fichier, TableauPoint);
=======
Specification lire_specification_tsp(FILE *fichier);

void lire_points_tsp(FILE *fichier, TableauPoint);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
Specification lecture_specification_tsp(FILE *fichier);

void lecture_points_tsp(FILE *fichier, TableauPoint);
>>>>>>> f2faa0f (rebase)

#endif // LECTURE_DONNEES_H
