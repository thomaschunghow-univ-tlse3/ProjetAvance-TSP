/*
 *
 * Ce module fournit :
 *  - Les types de coordonnées et de distances,
 *  - Les tableaux dynamiques de points et de distances (types abstraits),
 *  - Les demi-matrices de distances (type abstrait),
 *  - Les fonctions de création, accès, calcul et suppression de ces structures.
 */

#ifndef STRUCTURES_POINTS_H
#define STRUCTURES_POINTS_H

#include <stddef.h>

/* Définition d'une coordonnée.
 * Cela permet de modifier facilement la précision numérique. */
typedef double coordonnee;

/* Définition d'un point. */
typedef struct
{
    coordonnee x;
    coordonnee y;
} Point;

/* Type abstrait représentant un tableau dynamique de points. */
typedef struct tableau_points *TableauPoints;

TableauPoints creer_tableau_points(size_t nombre_points);
void supprimer_tableau_points(TableauPoints *);

size_t taille_tableau_points(TableauPoints);

Point *obtenir_element_tableau_points(TableauPoints, size_t indice);

#endif // STRUCTURES_POINTS_H
