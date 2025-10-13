/*
 * affichage.c
 */

#include "affichage.h"

#include <unistd.h>

void afficher_specification(FILE *sortie, Specification specification)
{
    fprintf(sortie,
            "%s\n"   // Nom
            "%s\n"   // Type
            "%s\n"   // Commentaire
            "%ld\n", // Nombre de points
            specification.nom,
            specification.type,
            specification.commentaire,
            specification.nombre_points);
}

void afficher_tableau_points(FILE *sortie, TableauPoints tableau)
{
    size_t nombre_points = taille_tableau_points(tableau);
    for (size_t i = 0; i < nombre_points; i++)
    {
        Point *point = obtenir_element_tableau_points(tableau, i);
        fprintf(sortie,
                "%ld "   // Indice du point
                "%lf "   // Coordonnée x
                "%lf\n", // Coordonnée y
                i + 1,
                point->x,
                point->y);
    }
}

void afficher_matrice(FILE *sortie, MatriceDistances matrice)
{
    size_t nombre_points = taille_tableau_points(tableau_points_matrice(matrice));
    for (size_t ligne = 0; ligne < nombre_points; ligne++)
    {
        for (size_t colonne = 0; colonne < ligne; colonne++)
        {
            distance *distance = obtenir_distance_matrice(matrice, ligne, colonne);
            fprintf(sortie,
                    "(%ld "  // Ligne
                    "%ld) "  // Colonne
                    "%lf\n", // Distance
                    ligne + 1,
                    colonne + 1,
                    *distance);
        }
    }
}

void afficher_tournee(FILE *sortie, TableauDistances tableau)
{
    size_t nombre_distances = taille_tableau_distances(tableau);
    fprintf(sortie, "[");
    for (size_t i = 0; i < nombre_distances; i++)
    {
        distance distance = *obtenir_element_tableau_distances(tableau, i);
        fprintf(sortie,
                "%lf,\n",
                distance);
    }
    fprintf(sortie, "]\n");
}