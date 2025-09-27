/*
 *
 */

#include "structures_de_donnees.h"

#include <stdio.h>
#include <stdlib.h>

ListePoints creer_liste_points(int nombre_points)
{
    ListePoints liste = malloc(nombre_points * sizeof(Point));
    if (liste == NULL)
    {
        fprintf(stderr, "creer_liste_points :\nEchec de l'allocation mémoire de la liste.\n");
        exit(EXIT_FAILURE);
    }
    return liste;
}

void supprimer_liste_points(ListePoints liste)
{
    free(liste);
}

ListeDistances creer_liste_distances(int nombre_distances)
{
    ListeDistances liste = malloc(nombre_distances * sizeof(distance));
    if (liste == NULL)
    {
        fprintf(stderr, "creer_liste_distances :\nEchec de l'allocation mémoire de la liste.\n");
        exit(EXIT_FAILURE);
    }
    return liste;
}

void supprimer_liste_distances(ListeDistances liste)
{
    free(liste);
}
