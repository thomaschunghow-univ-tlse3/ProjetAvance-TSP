/*
 * structure_distance.h
 *
 * Définitions et opérations sur les distances et tableaux de distance.
 */

#ifndef STRUCTURE_DISTANCE_H
#define STRUCTURE_DISTANCE_H

#include "structure_point.h"

#include <stddef.h>

typedef double distance;

typedef distance (*FonctionCalcul)(Point, Point);

typedef struct tableau_distance *TableauDistance;

TableauDistance tableau_distance_creer(size_t nombre_distances, FonctionCalcul);
void tableau_distance_supprimer(TableauDistance *);

size_t tableau_distance_obtenir_taille(TableauDistance);
FonctionCalcul tableau_distance_obtenir_fonction_calcul(TableauDistance);

distance tableau_distance_obtenir_distance(TableauDistance, size_t indice);
void tableau_distance_modifier_distance(TableauDistance, size_t indice, distance);

distance tableau_distance_calculer_somme(TableauDistance);

#endif // STRUCTURE_DISTANCE_H
