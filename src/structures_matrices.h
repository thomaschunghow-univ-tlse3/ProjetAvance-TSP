/*
 *
 * Ce module fournit :
 *  - Les types de coordonnées et de distances,
 *  - Les tableaux dynamiques de points et de distances (types abstraits),
 *  - Les demi-matrices de distances (type abstrait),
 *  - Les fonctions de création, accès, calcul et suppression de ces structures.
 */

#ifndef STRUCTURES_MATRICES_H
#define STRUCTURES_MATRICES_H

#include "structures_distances.h"

#include <stddef.h>

/* Définitions pour les demies-matrices.
 *
 * Une demie-matrice de distances représente une matrice carrée
 * où chaque élément correspond à une distance
 * entre un point de la ligne, et un point de la colonne.
 *
 * Pour économiser de la mémoire,
 * seule la partie triangulaire inférieure de la matrice
 * est stockée dans le tableau de distances (sans la diagonale).
 *
 * Remarque : pour alléger le code et les noms de fonctions,
 * nous utilisons le mot "matrice" pour désigner une demie-matrice.
 * En pratique, toutes les matrices manipulées ici
 * sont des demi-matrices. */

/* Type abstrait représentant la demie-matrice des distances
 * entre tous les points d’un tableau donné. */
typedef struct matrice_distances *MatriceDistances;

/* La création de la demie-matrice initialise le tableau des distances. */
MatriceDistances creer_matrice(TableauPoints, FonctionCalculDistance);

/* La création de la demi-matrice établit un lien avec le tableau de points.
 * La destruction de la matrice entraîne également
 * la suppression du tableau de points associé,
 * et celle du tableau de distances associé. */
void supprimer_matrice(MatriceDistances *);

TableauPoints tableau_points_matrice(MatriceDistances);
TableauDistances tableau_distances_matrice(MatriceDistances);

Point *obtenir_point_matrice(MatriceDistances, size_t indice);

/* Cette fonction permute elle-même la ligne et la colonne si besoin. */
distance *obtenir_distance_matrice(MatriceDistances, size_t ligne, size_t colonne);
size_t nombre_points_matrice(MatriceDistances);
size_t nombre_distances_matrice(MatriceDistances);
FonctionCalculDistance fonction_distance_matrice(MatriceDistances);

void verifier_element_dans_matrice(size_t ligne, size_t taille_points, size_t colonne);

size_t obtenir_indice_matrice(size_t ligne, size_t colonne);

#endif // STRUCTURES_MATRICES_H
