/*
 *
 */

#include "affichage.h"

#include <stdio.h>

void afficher_specification(Specification specification)
{
    printf("%s\n"  // Nom
           "%s\n"  // Type
           "%s\""  // Commentaire
           "%ld\n" // Nombre de points
           "%s\n", // Type de distance
           specification.nom,
           specification.type,
           specification.commentaire,
           specification.nombre_points,
           specification.type_distance);
}

void afficher_tableau_points(TableauPoints tableau)
{
    for (size_t i = 0; i < tableau.nombre_points; i++)
    {
        printf("%ld "   // Indice du point
               "%lf "   // Coordonnée x
               "%lf\n", // Coordonnée y
               i + 1,
               tableau.points[i].x,
               tableau.points[i].y);
    }
}

void afficher_matrice(MatriceDistances matrice)
{
    for (size_t i = 0; i < matrice.tableau_distances.nombre_distances; i++)
    {
        printf("%ld "   // Indice du point
               "%lf\n", // Distance
               i + 1,
               matrice.tableau_distances.distances[i]);
    }
}
