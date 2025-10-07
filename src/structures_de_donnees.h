/*
 *
 */

#ifndef STRUCTURES_DE_DONNEES_H
#define STRUCTURES_DE_DONNEES_H

#include <stddef.h>

typedef double coordonnee;
typedef struct
{
    coordonnee x;
    coordonnee y;
} Point;
typedef struct
{
    size_t nombre_points;
    Point *points;
} TableauPoints;

TableauPoints creer_tableau_points(size_t nombre_points);
void supprimer_tableau_points(TableauPoints *);

typedef double distance;
typedef distance (*calculer_distance)(Point, Point);
typedef struct
{
    size_t nombre_distances;
    distance *distances;
    calculer_distance calculer_distance;
} TableauDistances;

TableauDistances creer_tableau_distances(size_t nombre_distances, calculer_distance);
void supprimer_liste_distances(TableauDistances *);

typedef struct
{
    TableauPoints tableau_points;
    TableauDistances tableau_distances;
} MatriceDistances;



MatriceDistances creer_matrice(TableauPoints, calculer_distance);
void supprimer_matrice(MatriceDistances *);
size_t obtenir_element_matrice(MatriceDistances, size_t ligne, size_t colonne);
void remplir_matrice(MatriceDistances matrice);


#define TAILLE_CHAMP_MAX 100
typedef struct
{
    char nom[TAILLE_CHAMP_MAX];
    char type[TAILLE_CHAMP_MAX];
    char commentaire[TAILLE_CHAMP_MAX];
    size_t nombre_points;
    char type_distance[TAILLE_CHAMP_MAX];
} Specification;

#endif // STRUCTURES_DE_DONNEES_H
