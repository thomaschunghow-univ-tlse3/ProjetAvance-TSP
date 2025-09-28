/*
 *
 */

#include "structures_de_donnees.h"

#include <stdio.h>
#include <stdlib.h>

TableauPoints creer_tableau_points(size_t nombre_points)
{
    TableauPoints tableau;
    tableau.nombre_points = nombre_points;
    tableau.points = malloc(nombre_points * sizeof(Point));
    if (tableau.points == NULL)
    {
        printf("DEBUG\n");
        fprintf(stderr,
                "Erreur creer_tableau_points :\n"
                "Echec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }
    return tableau;
}

void supprimer_tableau_points(TableauPoints *tableau)
{
    free(tableau->points);
    tableau->nombre_points = 0;
    tableau->points = NULL;
}

TableauDistances creer_tableau_distances(size_t nombre_distances, calculer_distance calculer_distance)
{
    TableauDistances tableau;
    tableau.nombre_distances = nombre_distances;
    tableau.calculer_distance = calculer_distance;
    tableau.distances = malloc(nombre_distances * sizeof(distance));
    if (tableau.distances == NULL)
    {
        fprintf(stderr,
                "Erreur creer_tableau_distances :\n"
                "Echec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }
    return tableau;
}

void supprimer_liste_distances(TableauDistances *tableau)
{
    free(tableau->distances);
    tableau->nombre_distances = 0;
    tableau->distances = NULL;
}

size_t calculer_nombre_elements_matrice(size_t taille)
{
    return (taille * (taille - 1)) / 2;
}

MatriceDistances creer_matrice(TableauPoints tableau_points, calculer_distance calculer_distance)
{
    MatriceDistances matrice;
    matrice.tableau_points = tableau_points;
    size_t nombre_distances = calculer_nombre_elements_matrice(tableau_points.nombre_points);
    matrice.tableau_distances = creer_tableau_distances(nombre_distances, calculer_distance);
    return matrice;
}

void supprimer_matrice(MatriceDistances *matrice)
{
    supprimer_tableau_points(&matrice->tableau_points);
    supprimer_liste_distances(&matrice->tableau_distances);
}

size_t obtenir_element_matrice(MatriceDistances matrice, size_t ligne, size_t colonne)
{
    if (ligne == colonne)
    {
        fprintf(stderr,
                "Erreur obtenir_element_matrice :\n"
                "La distance d'un point à lui-même ne fait pas partie de la demie-matrice, car nulle.\n");
        exit(EXIT_FAILURE);
    }
    if (ligne < colonne)
    {
        fprintf(stderr,
                "Erreur obtenir_element_matrice :\n"
                "La ligne doit être strictement supérieure à la colonne, car la partie supérieur triangulaire de la matrice est vide.\n");
        exit(EXIT_FAILURE);
    }
    if (ligne >= matrice.tableau_points.nombre_points || colonne >= matrice.tableau_points.nombre_points)
    {
        fprintf(stderr,
                "Erreur obtenir_element_matrice :\n"
                "La ligne et/ou la colonne dépassent la taille de la matrice.\n");
        exit(EXIT_FAILURE);
    }
    return calculer_nombre_elements_matrice(ligne) + colonne;
}

void remplir_matrice(MatriceDistances matrice)
{
    Point *points = matrice.tableau_points.points;
    size_t nombre_points = matrice.tableau_points.nombre_points;
    distance *distances = matrice.tableau_distances.distances;
    calculer_distance calculer_distance = matrice.tableau_distances.calculer_distance;

    size_t indice_matrice = 0;
    for (size_t ligne = 0; ligne < nombre_points; ligne++)
    {
        for (size_t colonne = 0; colonne < ligne; colonne++)
        {
            distances[indice_matrice] = calculer_distance(points[ligne], points[colonne]);
            indice_matrice++;
        }
    }
}
