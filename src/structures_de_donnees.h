/*
 *
 */

#ifndef STRUCTURES_DE_DONNEES_H
#define STRUCTURES_DE_DONNEES_H

typedef double coordonnee;
typedef struct point
{
    coordonnee x;
    coordonnee y;
} Point;
typedef Point *ListePoints;

ListePoints creer_liste_points(int nombre_points);
void supprimer_liste_points(ListePoints);

typedef double distance;
typedef distance *ListeDistances;
typedef ListeDistances *MatriceDistances;
typedef distance (*calcul_distance)(Point, Point);

ListeDistances creer_liste_distances(int nombre_distances);
void supprimer_liste_distances(ListeDistances);

typedef struct demie_matrice_distances
{
    int nombre_points;
    ListePoints liste_points;
    MatriceDistances demie_matrice_distances;
    calcul_distance calcul_distance;
} DemieMatriceDistances;

MatriceDistances creer_demie_matrice_distances(int nombre_points);
void supprimer_demie_matrice_distances(MatriceDistances);

#endif // STRUCTURES_DE_DONNEES_H
