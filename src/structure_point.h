/*
 * structure_point.h
 *
 * Définitions et opérations sur les points et tableaux de point.
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

Point *tableau_point_obtenir_adresse(TableauPoint tableau);

Point tableau_point_obtenir_point(TableauPoint, size_t indice);
void tableau_point_modifier_point(TableauPoint, size_t indice, Point);

#endif // STRUCTURE_POINT_H
