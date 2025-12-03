/*
 * structure_point.c
 */

#include "structure_point.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TableauPoint tableau_point_creer(size_t nombre_points, size_t taille_point)
{
    TableauPoint tableau = malloc(sizeof(struct tableau_point) + nombre_points * taille_point);

    if (tableau == NULL)
    {
        fprintf(
            stderr,
            "Erreur tableau_point_creer :\n"
            "Échec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }

    tableau->nombre_points = nombre_points;
    tableau->taille_point = taille_point;

    tableau->points = (char *)(tableau + 1);

    return tableau;
}

void tableau_point_supprimer(TableauPoint *tableau)
{
    assert(tableau != NULL);
    assert(*tableau != NULL);

    free(*tableau);
    *tableau = NULL;
}

size_t tableau_point_obtenir_nombre_points(TableauPoint tableau)
{
    assert(tableau != NULL);

    return tableau->nombre_points;
}

size_t tableau_point_obtenir_taille_point(TableauPoint tableau)
{
    assert(tableau != NULL);

    return tableau->taille_point;
}

void tableau_point_obtenir_point(TableauPoint tableau, size_t indice, void *point_destination)
{
    assert(tableau != NULL);
    assert(indice < tableau_point_obtenir_nombre_points(tableau));
    assert(point_destination != NULL);

    size_t taille_point = tableau_point_obtenir_taille_point(tableau);

    memcpy(point_destination, tableau->points + indice * taille_point, taille_point);
}

void tableau_point_modifier_point(TableauPoint tableau, size_t indice, void *point_source)
{
    assert(tableau != NULL);
    assert(indice < tableau_point_obtenir_nombre_points(tableau));
    assert(point_source != NULL);

    size_t taille_point = tableau_point_obtenir_taille_point(tableau);

    memcpy(tableau->points + indice * taille_point, point_source, taille_point);
}
