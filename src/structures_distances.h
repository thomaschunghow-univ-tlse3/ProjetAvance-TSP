/*
 *
 * Ce module fournit :
 *  - Les types de coordonnées et de distances,
 *  - Les tableaux dynamiques de points et de distances (types abstraits),
 *  - Les demi-matrices de distances (type abstrait),
 *  - Les fonctions de création, accès, calcul et suppression de ces structures.
 */

#ifndef STRUCTURES_DISTANCES_H
#define STRUCTURES_DISTANCES_H

#include "structures_points.h"

#include <stddef.h>

/* Définition d'une coordonnée.
 * Cela permet de modifier facilement la précision numérique. */
typedef double distance;

/* Type abstrait représentant un tableau dynamique de distances.
 * Contient aussi une fonction de calcul associée. */
typedef struct tableau_distances *TableauDistances;

typedef distance (*FonctionCalculDistance)(Point, Point);

TableauDistances creer_tableau_distances(size_t nombre_distances, FonctionCalculDistance);
void supprimer_tableau_distances(TableauDistances *);

size_t taille_tableau_distances(TableauDistances);
FonctionCalculDistance fonction_tableau_distances(TableauDistances);

distance *obtenir_element_tableau_distances(TableauDistances, size_t indice);

distance somme_tableau_distances(TableauDistances);

#endif // STRUCTURES_DISTANCES_H
