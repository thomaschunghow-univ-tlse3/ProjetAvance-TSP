/*
 * structure_tableau_permutation.c
 */

#include "structure_tableau_permutation.h"

#include "structure_permutation_interne.h"
#include "structure_tableau_permutation_interne.h"

#include "nombre_aleatoire.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TableauPermutation tableau_permutation_creer(size_t nombre_permutations, size_t nombre_sommets, size_t taille_distance)
{
    TableauPermutation tableau =
        malloc(sizeof(struct tableau_permutation) +
               nombre_permutations * (sizeof(struct permutation) + nombre_sommets * sizeof(size_t) + taille_distance));

    if (tableau == NULL)
    {
        fprintf(stderr, "Erreur tableau_permutation_creer :\n"
                        "Échec de l'allocation mémoire de la permutation.\n");
        exit(EXIT_FAILURE);
    }

    tableau->nombre_permutations = nombre_permutations;
    tableau->permutations = (struct permutation *)(tableau + 1);

    size_t *adresse_sommets = (size_t *)(tableau->permutations + nombre_permutations);
    char *adresse_longueur = (char *)(adresse_sommets + nombre_permutations * nombre_sommets);

    for (size_t i = 0; i < nombre_permutations; i++)
    {
        Permutation permutation = tableau->permutations + i;

        permutation->nombre_sommets = nombre_sommets;
        permutation->sommets = adresse_sommets + nombre_sommets * i;
        permutation->taille_distance = taille_distance;
        permutation->longueur = adresse_longueur + taille_distance * i;

        permutation_initialiser(permutation);
    }

    return tableau;
}

void tableau_permutation_supprimer(TableauPermutation *tableau)
{
    assert(tableau != NULL);
    assert(*tableau != NULL);

    free(*tableau);
    *tableau = NULL;
}

size_t tableau_permutation_obtenir_nombre_permutations(TableauPermutation tableau)
{
    assert(tableau != NULL);

    return tableau->nombre_permutations;
}

Permutation tableau_permutation_obtenir_permutation(TableauPermutation tableau, size_t indice)
{
    assert(tableau != NULL);
    assert(indice < tableau->nombre_permutations);

    return tableau->permutations + indice;
}

size_t tableau_permutation_trouver_pire_individu(TableauPermutation tableau, DistanceComparer distance_comparer)
{
    assert(tableau != NULL);

    size_t nombre_permutations = tableau_permutation_obtenir_nombre_permutations(tableau);

    size_t indice_pire_individu = 0;
    char *longueur_pire_individu = tableau->permutations[indice_pire_individu].longueur;

    for (size_t i = 1; i < nombre_permutations; i++)
    {
        char *longueur = tableau->permutations[i].longueur;

        if (distance_comparer(longueur, longueur_pire_individu) > 0)
        {
            indice_pire_individu = i;
            longueur_pire_individu = tableau->permutations[indice_pire_individu].longueur;
        }
    }

    return indice_pire_individu;
}

size_t tableau_permutation_trouver_meilleur_individu(TableauPermutation tableau, DistanceComparer distance_comparer)
{
    assert(tableau != NULL);

    size_t nombre_permutations = tableau_permutation_obtenir_nombre_permutations(tableau);

    size_t indice_meilleur_individu = 0;
    char *longueur_meilleur_individu = tableau->permutations[indice_meilleur_individu].longueur;

    for (size_t i = 1; i < nombre_permutations; i++)
    {
        char *longueur = tableau->permutations[i].longueur;

        if (distance_comparer(longueur, longueur_meilleur_individu) < 0)
        {
            indice_meilleur_individu = i;
            longueur_meilleur_individu = tableau->permutations[indice_meilleur_individu].longueur;
        }
    }

    return indice_meilleur_individu;
}

void tableau_permutation_echanger_tableaux(TableauPermutation *tableau_A, TableauPermutation *tableau_B)
{
    assert(tableau_A != NULL);
    assert(*tableau_A != NULL);
    assert(tableau_B != NULL);
    assert(*tableau_B != NULL);

    TableauPermutation temp = *tableau_A;
    *tableau_A = *tableau_B;
    *tableau_B = temp;
}

DistanceComparer distance_comparer_pour_qsort;

int tableau_permutation_comparer(const void *A, const void *B)
{
    Permutation permutation_A = (Permutation)A;
    Permutation permutation_B = (Permutation)B;

    return distance_comparer_pour_qsort(permutation_A->longueur, permutation_B->longueur);
}

void tableau_permutation_trier(TableauPermutation tableau, DistanceComparer distance_comparer)
{
    assert(tableau != NULL);

    size_t nombre_permutations = tableau_permutation_obtenir_nombre_permutations(tableau);

    distance_comparer_pour_qsort = distance_comparer;

    qsort(tableau->permutations, nombre_permutations, sizeof(struct permutation), tableau_permutation_comparer);
}

void tableau_permutation_obtenir_longueur(TableauPermutation tableau, size_t indice, void *longueur_destination)
{
    permutation_obtenir_longueur(tableau->permutations + indice, longueur_destination);
}

void tableau_permutation_modifier_longueur(TableauPermutation tableau, size_t indice, void *longueur_source)
{
    permutation_modifier_longueur(tableau->permutations + indice, longueur_source);
}
