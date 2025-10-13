/*
 */

#include "structures_matrices.h"

#include <stdio.h>
#include <stdlib.h>

struct matrice_distances
{
    TableauPoints tableau_points;
    TableauDistances tableau_distances;
};

size_t nombre_elements_demie_matrice(size_t ligne)
{
    return (ligne * (ligne - 1)) / 2;
}

void calculer_element_matrice(MatriceDistances matrice, size_t ligne, size_t colonne)
{
    TableauPoints points = tableau_points_matrice(matrice);
    TableauDistances distances = tableau_distances_matrice(matrice);
    FonctionCalculDistance calculer_distance = fonction_tableau_distances(distances);

    verifier_element_dans_matrice(taille_tableau_points(points), ligne, colonne);

    Point point_ligne = *obtenir_element_tableau_points(points, ligne);
    Point point_colonne = *obtenir_element_tableau_points(points, colonne);
    distance distance_calculee = calculer_distance(point_ligne, point_colonne);

    distance *distance_matrice = obtenir_element_tableau_distances(distances, obtenir_indice_matrice(ligne, colonne));
    *distance_matrice = distance_calculee;
}

void remplir_matrice(MatriceDistances matrice)
{
    TableauPoints points = tableau_points_matrice(matrice);
    size_t nombre_points = taille_tableau_points(points);
    for (size_t ligne = 0; ligne < nombre_points; ligne++)
    {

        for (size_t colonne = 0; colonne < ligne; colonne++)
        {
            calculer_element_matrice(matrice, ligne, colonne);
        }
    }
}

MatriceDistances creer_matrice(TableauPoints tableau_points, FonctionCalculDistance calculer_distance)
{
    MatriceDistances matrice;
    matrice = malloc(sizeof(struct matrice_distances));
    matrice->tableau_points = tableau_points;
    size_t nombre_distances = nombre_elements_demie_matrice(taille_tableau_points(tableau_points));
    matrice->tableau_distances = creer_tableau_distances(nombre_distances, calculer_distance);
    remplir_matrice(matrice);
    return matrice;
}

void verifier_matrice_non_vide(MatriceDistances matrice)
{
    if (matrice == NULL)
    {
        fprintf(stderr,
                "Erreur verifier_matrice_non_vide :\n"
                "Matrice de distances vide.\n");
        exit(EXIT_FAILURE);
    }
}

void supprimer_matrice(MatriceDistances *matrice)
{
    verifier_matrice_non_vide(*matrice);
    TableauPoints points = tableau_points_matrice(*matrice);
    TableauDistances distances = tableau_distances_matrice(*matrice);

    supprimer_tableau_points(&points);
    supprimer_tableau_distances(&distances);
    free(*matrice);
    *matrice = NULL;
}

TableauPoints tableau_points_matrice(MatriceDistances matrice)
{
    verifier_matrice_non_vide(matrice);
    return matrice->tableau_points;
}

TableauDistances tableau_distances_matrice(MatriceDistances matrice)
{
    verifier_matrice_non_vide(matrice);
    return matrice->tableau_distances;
}

Point *obtenir_point_matrice(MatriceDistances matrice, size_t indice)
{
    verifier_matrice_non_vide(matrice);
    TableauPoints points = tableau_points_matrice(matrice);
    return obtenir_element_tableau_points(points, indice);
}

void verifier_element_dans_matrice(size_t taille_points, size_t ligne, size_t colonne)
{
    if (ligne >= taille_points || colonne >= taille_points)
    {
        fprintf(stderr,
                "Erreur obtenir_distance_matrice :\n"
                "La ligne et/ou la colonne dépassent la taille de la matrice.\n");
        exit(EXIT_FAILURE);
    }
}

void echanger(size_t *ligne, size_t *colonne)
{
    size_t temp = *ligne;
    *ligne = *colonne;
    *colonne = temp;
}

size_t obtenir_indice_matrice(size_t ligne, size_t colonne)
{
    return nombre_elements_demie_matrice(ligne) + colonne;
}

distance *obtenir_distance_matrice(MatriceDistances matrice, size_t ligne, size_t colonne)
{
    verifier_matrice_non_vide(matrice);
    TableauPoints points = tableau_points_matrice(matrice);
    TableauDistances distances = tableau_distances_matrice(matrice);
    verifier_element_dans_matrice(taille_tableau_points(points), ligne, colonne);
    if (ligne == colonne)
    {
        fprintf(stderr,
                "Erreur obtenir_element_matrice :\n"
                "La distance d'un point à lui-même ne fait pas partie de la demie-matrice, car nulle.\n");
        exit(EXIT_FAILURE);
    }
    if (ligne < colonne)
    {
        echanger(&ligne, &colonne);
    }
    return obtenir_element_tableau_distances(distances, obtenir_indice_matrice(ligne, colonne));
}

size_t nombre_points_matrice(MatriceDistances matrice)
{
    return taille_tableau_points(tableau_points_matrice(matrice));
}

size_t nombre_distances_matrice(MatriceDistances matrice)
{
    return taille_tableau_distances(tableau_distances_matrice(matrice));
}

FonctionCalculDistance fonction_distance_matrice(MatriceDistances matrice)
{
    return fonction_tableau_distances(tableau_distances_matrice(matrice));
}
