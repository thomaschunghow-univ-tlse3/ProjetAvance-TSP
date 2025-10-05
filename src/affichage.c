/*
 *
 */

#include "affichage.h"
#include <stdlib.h>
#include <stdio.h>

void afficher_specification(Specification specification)
{
    printf("Nom : %s\n"  // Nom
           "Type : %s\n"  // Type
           "Commentaire : %s\n"  // Commentaire
           "NB point : %ld\n" // Nombre de points
           "Type de distance %s\n", // Type de distance
           specification.nom,
           specification.type,
           specification.commentaire,
           specification.nombre_points,
           specification.type_distance);
}

void afficher_liste_points(TableauPoints liste)
{
    for (size_t i = 0; i < liste.nombre_points; i++)
    {
		
        printf("indice %ld "   // Indice du point
               "x : %lf "   // Coordonnée x
               "y : %lf\n", // Coordonnée y
               i + 1,
               liste.points[i].x,
               liste.points[i].y);
    }
}

void afficher_matrice(MatriceDistances matrice)
{
    for (size_t i = 0; i < matrice.tableau_distances.nombre_distances; i++)
    {
        printf("indice : %ld "   // Indice du point
               "distance : %lf\n", // Distance
               i + 1,
               matrice.tableau_distances.distances[i]);
    }
}

/*void afficher_extremite(Extremite *extremite){
	printf(" meilleure distance : %f, pire distance : %f\n",extremite -> meilleurDistance,extremite -> pireDistance);
}*/
