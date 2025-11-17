/*
 * structure_distance.c
 */

#include "structure_distance.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct tableau_distance
{
    FonctionCalcul calculer_distance;

    size_t nombre_distances;
    distance *distances;
};

TableauDistance tableau_distance_creer(size_t nombre_distances, FonctionCalcul calculer_distance)
{
    TableauDistance tableau = malloc(sizeof(struct tableau_distance) +
                                     nombre_distances * sizeof(distance));

    if (tableau == NULL)
    {
        fprintf(stderr,
                "Erreur tableau_distance_creer :\n"
                "Echec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }

    tableau->calculer_distance = calculer_distance;
    tableau->nombre_distances = nombre_distances;
    tableau->distances = (distance *)(tableau + 1);

    return tableau;
}

void tableau_distance_assert_non_vide(TableauDistance tableau)
{
    assert(tableau != NULL);
    (void)tableau;
}

void tableau_distance_assert_indice_valide(TableauDistance tableau, size_t indice)
{
    assert(indice < tableau_distance_obtenir_taille(tableau));
    (void)tableau;
    (void)indice;
}

void tableau_distance_supprimer(TableauDistance *tableau)
{
    tableau_distance_assert_non_vide(*tableau);

    free(*tableau);
    *tableau = NULL;
}

FonctionCalcul tableau_distance_obtenir_fonction_calcul(TableauDistance tableau)
{
    tableau_distance_assert_non_vide(tableau);

    return tableau->calculer_distance;
}

size_t tableau_distance_obtenir_taille(TableauDistance tableau)
{
    tableau_distance_assert_non_vide(tableau);

    return tableau->nombre_distances;
}

distance tableau_distance_obtenir_distance(TableauDistance tableau, size_t indice)
{
    tableau_distance_assert_non_vide(tableau);

    tableau_distance_assert_indice_valide(tableau, indice);
    return tableau->distances[indice];
}

void tableau_distance_modifier_distance(TableauDistance tableau, size_t indice, distance distance)
{
    tableau_distance_assert_non_vide(tableau);

    tableau_distance_assert_indice_valide(tableau, indice);

    tableau->distances[indice] = distance;
}

distance tableau_distance_calculer_somme(TableauDistance tableau)
{
    tableau_distance_assert_non_vide(tableau);

    size_t taille_tableau = tableau_distance_obtenir_taille(tableau);

    distance somme = 0;
    for (size_t i = 0; i < taille_tableau; i++)
    {
        somme += tableau_distance_obtenir_distance(tableau, i);
    }

    return somme;
}
