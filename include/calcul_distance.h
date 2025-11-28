/*
 * calcul_distance.h
 *
 * Fonctions de calcul de distance.
 */

#ifndef CALCUL_DISTANCE_H
#define CALCUL_DISTANCE_H

#include "structure.h"

#define PI 3.14159265358979323846
#define RACINE_10 3.16227766016837952279
#define RAYON_TERRE 6378.388

typedef double coordonnee;

typedef struct
{
    coordonnee x;
    coordonnee y;
} Point;

typedef double distance;

typedef enum
{
    EUC_2D,
    GEO,
    ATT
} TypeDistance;

size_t calculer_factorielle(size_t);

void calculer_distance_euclidienne_generique(void *point_A, void *point_B, void *longueur_AB);
void calculer_distance_geographique_generique(void *point_A, void *point_B, void *longueur_AB);
void calculer_distance_euclidienne_modifiee_generique(void *point_A, void *point_B, void *longueur_AB);

void distance_additionner(void *distance_A, void *distance_B, void *somme);
void distance_soustraire(void *distance_A, void *distance_B, void *difference);
int distance_comparer(void *distance_A, void *distance_B);

#endif // CALCUL_DISTANCE_H
