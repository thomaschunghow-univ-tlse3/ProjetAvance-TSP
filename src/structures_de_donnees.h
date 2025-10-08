/*
 * structures_de_donnees.h
 *
 * Ce module fournit :
 *  - Les types de coordonnées et de distances,
 *  - Les tableaux dynamiques de points et de distances (types abstraits),
 *  - Les demi-matrices de distances (type abstrait),
 *  - Les fonctions de création, accès, calcul et suppression de ces structures.
 */

#ifndef STRUCTURES_DE_DONNEES_H
#define STRUCTURES_DE_DONNEES_H

#include <stddef.h>

/* Définitions pour les types de coordonnées et de distances.
 * Cela permet de modifier facilement la précision numérique.

 * Si l'on change la précision numérique ici, il faut aussi changer accordément
 * le type dans le sprintf de la fonction de lecture des données. */

typedef double coordonnee;
typedef double distance;

/* Définitions pour les tableaux de points. */

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

/* Définitions pour les tableaux de distances. */

/* Type abstrait représentant un tableau dynamique de distances.
 * Contient aussi une fonction de calcul associée. */
typedef struct tableau_distances *TableauDistances;

typedef distance (*calculer_distance)(Point, Point);

TableauDistances creer_tableau_distances(size_t nombre_distances, calculer_distance);
void supprimer_tableau_distances(TableauDistances *);

size_t taille_tableau_distances(TableauDistances);
calculer_distance fonction_tableau_distances(TableauDistances);

distance *obtenir_element_tableau_distances(TableauDistances, size_t indice);

distance somme_tableau_distances(TableauDistances);

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

/* La création de la demie-matrice n'initialise pas le tableau des distances.
 * Il revient à l'utilisateur de calculer élément par élément les distances souhaitées,
 * ou bien de calculer tout le tableau à l'aide de la fonction remplir. */
MatriceDistances creer_matrice(TableauPoints, calculer_distance);
/* La création de la demi-matrice établit un lien avec le tableau de points.
 * La destruction de la matrice entraîne également
 * la suppression du tableau de points associé,
 * et celle du tableau de distances associé. */
void supprimer_matrice(MatriceDistances *);

TableauPoints tableau_points_matrice(MatriceDistances);
TableauDistances tableau_distances_matrice(MatriceDistances);

Point *obtenir_point_matrice(MatriceDistances, size_t indice);
distance *obtenir_distance_matrice(MatriceDistances, size_t ligne, size_t colonne);

void verifier_element_dans_matrice(size_t ligne, size_t taille_points, size_t colonne);

size_t obtenir_indice_matrice(size_t ligne, size_t colonne);

/* Calcule la distance entre deux points demandés,
 * et la conserve dans le tableau de distances de la matrice. */
void calculer_element_matrice(MatriceDistances, size_t ligne, size_t colonne);

/* Calcule la distance entre chaque coordoonnée de la matrice de distances
 * et la conserve dans le tableau de distances de la matrice. */
void remplir_matrice(MatriceDistances);

#endif // STRUCTURES_DE_DONNEES_H
