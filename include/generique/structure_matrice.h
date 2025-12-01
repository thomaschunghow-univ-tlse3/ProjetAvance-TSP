/*
 * structure_matrice.h
 */

#ifndef STRUCTURE_MATRICE_H
#define STRUCTURE_MATRICE_H

#include <stdbool.h>
#include <stddef.h>

void size_t_echanger(size_t *A, size_t *B);

typedef struct tableau_point *TableauPoint;

typedef struct tableau_distance *TableauDistance;

typedef void (*DistanceCalculer)(void *point_A, void *point_B, void *distance);
typedef void (*DistanceAdditionner)(void *distance_A, void *distance_B, void *somme);
typedef void (*DistanceSoustraire)(void *distance_A, void *distance_B, void *difference);
/* Retourne une valeur inférieure à 0 si distance_A < distance_B,
 * retourne 0 si distance_A == distance_B,
 * retourne une valeur supérieure à 0 si distance_A > distance_B. */
typedef int (*DistanceComparer)(void *distance_A, void *distance_B);

/*
 * Matrice :
 * Définition et opérations du type abstrait de demi-matrice de distance.
 *
 * Pour économiser de la mémoire,
 * seule la partie triangulaire inférieure de la matrice
 * est stockée dans le tableau de distance (sans la diagonale, car nulle).
 *
 * Remarque : pour alléger le code et les noms des fonctions,
 * nous utilisons le mot "matrice" pour désigner une demi-matrice.
 * En pratique, toutes les matrices manipulées ici sont des demi-matrices.
 */

typedef struct matrice_distance *MatriceDistance;

MatriceDistance matrice_creer(
    size_t nombre_points, size_t taille_point, size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer);
void matrice_supprimer(MatriceDistance *);

size_t matrice_obtenir_nombre_points(MatriceDistance);
size_t matrice_obtenir_taille_point(MatriceDistance matrice);

size_t matrice_obtenir_nombre_distances(MatriceDistance);
size_t matrice_obtenir_taille_distance(MatriceDistance matrice);

DistanceCalculer matrice_obtenir_distance_calculer(MatriceDistance);
DistanceAdditionner matrice_obtenir_distance_additionner(MatriceDistance matrice);
DistanceSoustraire matrice_obtenir_distance_soustraire(MatriceDistance matrice);
DistanceComparer matrice_obtenir_distance_comparer(MatriceDistance matrice);

void matrice_obtenir_point(MatriceDistance, size_t indice, void *point_destination);
void matrice_modifier_point(MatriceDistance, size_t indice, void *point_destination);

void matrice_obtenir_distance(MatriceDistance, size_t ligne, size_t colonne, void *distance_destination);
void matrice_remplir(MatriceDistance);

int matrice_comparer_distances(MatriceDistance, size_t ligne_A, size_t colonne_A, size_t ligne_B, size_t colonne_B);

#endif // STRUCTURE_MATRICE_H
