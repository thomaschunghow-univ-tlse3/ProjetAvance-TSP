/*
 */

#include "structures_points.h"

#include <stdio.h>
#include <stdlib.h>

struct tableau_points
{
    size_t nombre_points;
    Point *points;
};

TableauPoints creer_tableau_points(size_t nombre_points)
{
    TableauPoints tableau = malloc(sizeof(struct tableau_points) + nombre_points * sizeof(Point));
    if (tableau == NULL)
    {
        printf("DEBUG\n");
        fprintf(stderr,
                "Erreur creer_tableau_points :\n"
                "Echec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }
    tableau->nombre_points = nombre_points;
    tableau->points = (Point *)(tableau + 1);
    return tableau;
}

void verifier_tableau_points_non_vide(TableauPoints tableau)
{
    if (tableau == NULL)
    {
        fprintf(stderr,
                "Erreur verifier_tableau_points_non_vide :\n"
                "Tableau de points vide.\n");
        exit(EXIT_FAILURE);
    }
}

void supprimer_tableau_points(TableauPoints *tableau)
{
    verifier_tableau_points_non_vide(*tableau);
    free(*tableau);
    *tableau = NULL;
}

size_t taille_tableau_points(TableauPoints tableau)
{
    verifier_tableau_points_non_vide(tableau);
    return tableau->nombre_points;
}

Point *obtenir_element_tableau_points(TableauPoints tableau, size_t indice)
{
    verifier_tableau_points_non_vide(tableau);
    if (indice >= taille_tableau_points(tableau))
    {
        fprintf(stderr,
                "Erreur obtenir_element_tableau_points :\n"
                "L'indice dépasse la taille du tableau.\n");
        exit(EXIT_FAILURE);
    }
    return tableau->points + indice;
}
