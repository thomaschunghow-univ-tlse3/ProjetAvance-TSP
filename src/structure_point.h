/*
 * structure_point.h
 *
 * Ce module fournit :
 *  - La définition d'une coordonnée,
 *  - La définition d'un point,
 *  - La définition d'un type abstrait de données, représentant un tableau de point,
 *  - Les fonctions de création, de suppression, et d'accès aux tableaux de point.
 */

#ifndef STRUCTURE_POINT_H
#define STRUCTURE_POINT_H

#include <stddef.h>

typedef double coordonnee;

typedef struct
{
    coordonnee x;
    coordonnee y;
} Point;

typedef struct tableau_point *TableauPoint;

TableauPoint tableau_point_creer(size_t nombre_points);
void tableau_point_supprimer(TableauPoint *);

size_t tableau_point_obtenir_taille(TableauPoint);

Point tableau_point_obtenir_point(TableauPoint, size_t indice);
void tableau_point_modifier_point(TableauPoint, size_t indice, Point);

#endif // STRUCTURE_POINT_H
