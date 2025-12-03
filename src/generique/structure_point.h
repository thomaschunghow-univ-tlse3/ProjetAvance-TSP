/*
 * structure_point.h
 */

#ifndef STRUCTURE_POINT_H
#define STRUCTURE_POINT_H

#include "structure_matrice_interne.h"

#include <stddef.h>

TableauPoint tableau_point_creer(size_t nombre_points, size_t taille_point);
void tableau_point_supprimer(TableauPoint *);

size_t tableau_point_obtenir_nombre_points(TableauPoint);
size_t tableau_point_obtenir_taille_point(TableauPoint);

void tableau_point_obtenir_point(TableauPoint, size_t indice, void *point_destination);
void tableau_point_modifier_point(TableauPoint, size_t indice, void *point_source);

#endif // STRUCTURE_POINT_H
