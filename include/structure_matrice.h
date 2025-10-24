/*
 * structure_matrice.h
 *
 * Définitions et opérations sur les demi-matrices de distance.
 *
 * Une demi-matrice de distances représente une matrice carrée
 * où chaque élément correspond à une distance
 * entre un point de la ligne, et un point de la colonne.
 *
 * Pour économiser de la mémoire,
 * seule la partie triangulaire inférieure de la matrice
 * est stockée dans le tableau de distances (sans la diagonale, car nulle).
 *
 * Remarque : pour alléger le code et les noms de fonctions,
 * nous utilisons le mot "matrice" pour désigner une demi-matrice.
 * En pratique, toutes les matrices manipulées ici sont des demi-matrices.
 */

#ifndef STRUCTURE_MATRICE_H
#define STRUCTURE_MATRICE_H

#include "structure_distance.h"

typedef struct matrice_distance *MatriceDistance;

MatriceDistance matrice_creer(size_t nombre_points, FonctionCalcul);
void matrice_supprimer(MatriceDistance *);

void matrice_remplir_distance(MatriceDistance matrice);

TableauPoint matrice_obtenir_tableau_point(MatriceDistance);
TableauDistance matrice_obtenir_tableau_distance(MatriceDistance);

size_t matrice_obtenir_nombre_points(MatriceDistance);
size_t matrice_obtenir_nombre_distances(MatriceDistance);
FonctionCalcul matrice_obtenir_fonction_calcul(MatriceDistance);

Point matrice_obtenir_point(MatriceDistance, size_t indice);
distance matrice_obtenir_distance(MatriceDistance, size_t ligne, size_t colonne);

void echanger(size_t *ligne, size_t *colonne);

#endif // STRUCTURE_MATRICE_H
