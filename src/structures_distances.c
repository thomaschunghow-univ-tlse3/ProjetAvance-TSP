/*
 */

#include "structures_distances.h"

#include <stdio.h>
#include <stdlib.h>

struct tableau_distances
{
    size_t nombre_distances;
    distance *distances;
    FonctionCalculDistance calculer_distance;
};

TableauDistances creer_tableau_distances(size_t nombre_distances, FonctionCalculDistance calculer_distance)
{
    TableauDistances tableau = malloc(sizeof(struct tableau_distances) + nombre_distances * sizeof(distance));
    if (tableau == NULL)
    {
        fprintf(stderr,
                "Erreur creer_tableau_distances :\n"
                "Echec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }
    tableau->nombre_distances = nombre_distances;
    tableau->calculer_distance = calculer_distance;
    tableau->distances = (distance *)(tableau + 1);
    return tableau;
}

void verifier_tableau_distances_non_vide(TableauDistances tableau)
{
    if (tableau == NULL)
    {
        fprintf(stderr,
                "Erreur verifier_tableau_distances_non_vide :\n"
                "Tableau de distances vide.\n");
        exit(EXIT_FAILURE);
    }
}

void supprimer_tableau_distances(TableauDistances *tableau)
{
    verifier_tableau_distances_non_vide(*tableau);
    free(*tableau);
    *tableau = NULL;
}

size_t taille_tableau_distances(TableauDistances tableau)
{
    verifier_tableau_distances_non_vide(tableau);
    return tableau->nombre_distances;
}

FonctionCalculDistance fonction_tableau_distances(TableauDistances tableau)
{
    verifier_tableau_distances_non_vide(tableau);
    return tableau->calculer_distance;
}

distance *obtenir_element_tableau_distances(TableauDistances tableau, size_t indice)
{
    verifier_tableau_distances_non_vide(tableau);
    if (indice >= taille_tableau_distances(tableau))
    {
        fprintf(stderr,
                "Erreur obtenir_element_tableau_distances :\n"
                "L'indice dépasse la taille du tableau.\n");
        exit(EXIT_FAILURE);
    }
    return tableau->distances + indice;
}

distance somme_tableau_distances(TableauDistances tableau)
{
    verifier_tableau_distances_non_vide(tableau);
    distance somme = 0;
    size_t taille_tableau = taille_tableau_distances(tableau);
    for (size_t i = 0; i < taille_tableau; i++)
    {
        somme += *obtenir_element_tableau_distances(tableau, i);
    }
    return somme;
}
