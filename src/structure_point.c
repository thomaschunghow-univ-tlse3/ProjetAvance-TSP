/*
 * structure_point.c
 */

#include "structure_point.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct tableau_point
{
    size_t nombre_points;
    Point *points;
};

TableauPoint tableau_point_creer(size_t nombre_points)
{
    TableauPoint tableau = malloc(sizeof(struct tableau_point) +
                                  nombre_points * sizeof(Point));

    if (tableau == NULL)
    {
        fprintf(stderr,
                "Erreur tableau_point_creer :\n"
                "Echec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }

    tableau->nombre_points = nombre_points;
    tableau->points = (Point *)(tableau + 1);

    return tableau;
}

void tableau_point_assert_non_vide(TableauPoint tableau)
{
    assert(tableau != NULL);
    (void)tableau;
}

void tableau_point_assert_indice_valide(TableauPoint tableau, size_t indice)
{
    assert(indice < tableau_point_obtenir_taille(tableau));
    (void)tableau;
    (void)indice;
}

void tableau_point_supprimer(TableauPoint *tableau)
{
    tableau_point_assert_non_vide(*tableau);

    free(*tableau);
    *tableau = NULL;
}

size_t tableau_point_obtenir_taille(TableauPoint tableau)
{
    tableau_point_assert_non_vide(tableau);

    return tableau->nombre_points;
}

Point tableau_point_obtenir_point(TableauPoint tableau, size_t indice)
{
    tableau_point_assert_non_vide(tableau);

    tableau_point_assert_indice_valide(tableau, indice);

    return tableau->points[indice];
}

void tableau_point_modifier_point(TableauPoint tableau, size_t indice, Point point)
{
    tableau_point_assert_non_vide(tableau);

    tableau_point_assert_indice_valide(tableau, indice);

    tableau->points[indice] = point;
}
