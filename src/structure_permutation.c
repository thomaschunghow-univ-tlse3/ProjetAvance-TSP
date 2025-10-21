/*
 * structure_permutation.c
 */

#include "structure_permutation.h"

#include <stdio.h>
#include <stdlib.h>

struct permutation
{
    size_t nombre_indices;
    size_t *indices;
};

void permutation_initialiser(Permutation permutation)
{
    for (size_t i = 0; i < permutation_obtenir_taille(permutation); i++)
    {
        permutation->indices[i] = i;
    }
}

Permutation permutation_creer(size_t nombre_indices)
{
    Permutation permutation = malloc(sizeof(struct permutation) +
                                     nombre_indices * sizeof(size_t));

    if (permutation == NULL)
    {
        fprintf(stderr,
                "Erreur permutation_creer :\n"
                "Echec de l'allocation mémoire de la permutation.\n");
        exit(EXIT_FAILURE);
    }

    permutation->nombre_indices = nombre_indices;
    permutation->indices = (size_t *)(permutation + 1);

    permutation_initialiser(permutation);

    return permutation;
}

void permutation_assert_non_vide(Permutation permutation)
{
    if (permutation == NULL)
    {
        fprintf(stderr,
                "Erreur permutation_assert_non_vide :\n"
                "Permutation vide.\n");
        exit(EXIT_FAILURE);
    }
}

void permutation_assert_indice_valide(Permutation permutation, size_t indice)
{
    if (indice >= permutation_obtenir_taille(permutation))
    {
        fprintf(stderr,
                "Erreur permutation_assert_indice_valide :\n"
                "L'indice dépasse la taille de la permutation.\n");
        exit(EXIT_FAILURE);
    }
}

void permutation_supprimer(Permutation *permutation)
{
    permutation_assert_non_vide(*permutation);

    free(*permutation);
    *permutation = NULL;
}

size_t permutation_obtenir_taille(Permutation permutation)
{
    permutation_assert_non_vide(permutation);

    return permutation->nombre_indices;
}

size_t permutation_obtenir_indice(Permutation permutation, size_t indice)
{
    permutation_assert_non_vide(permutation);

    return permutation->indices[indice];
}

void permutation_echanger_indices(Permutation permutation, int i, int j)
{
    permutation_assert_non_vide(permutation);

    permutation_assert_indice_valide(permutation, i);
    permutation_assert_indice_valide(permutation, j);

    size_t *indices = permutation->indices;

    size_t temp = indices[i];
    indices[i] = indices[j];
    indices[j] = temp;
}

distance permutation_calculer_distance_totale(Permutation permutation, MatriceDistance matrice)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_indices = permutation_obtenir_taille(permutation);
    size_t *indices = permutation->indices;

    distance distance_totale = matrice_obtenir_distance(matrice, indices[0], indices[nombre_indices - 1]);
    for (size_t i = 0; i < nombre_indices - 1; i++)
    {
        distance_totale += matrice_obtenir_distance(matrice, indices[i], indices[i + 1]);
    }

    return distance_totale;
}

void permutation_copier(Permutation destination, Permutation source)
{
    for (size_t i = 0; i < permutation_obtenir_taille(destination); i++)
    {
        destination->indices[i] = source->indices[i];
    }
}

bool permutation_avancer(Permutation permutation)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_indices = permutation_obtenir_taille(permutation);
    size_t *indices = permutation->indices;

    if (nombre_indices == 0)
    {
        return false;
    }

    size_t pivot = nombre_indices - 1;

    /* On cherche le plus petit indice, tel que ceux d'après déterminent une séquence strictement décroissante.
     * Cette séquence s'appelle le suffixe. */
    while (pivot > 1 && indices[pivot - 1] >= indices[pivot])
    {
        pivot--;
    }

    /* Si ce plus petit indice est 1, alors le tableau après le premier indice est totalement décroissant.
     * On a donc atteint la dernière permutation. */
    if (pivot == 1)
    {
        return false;
    }

    /* On cherche l’indice le plus petit du suffixe qui est plus grand que le pivot. */
    size_t successeur = nombre_indices - 1;
    while (indices[successeur] <= indices[pivot - 1])
    {
        successeur--;
    }

    permutation_echanger_indices(permutation, pivot - 1, successeur);

    /* On inverse le suffixe. */
    successeur = nombre_indices - 1;
    while (pivot < successeur)
    {
        permutation_echanger_indices(permutation, pivot, successeur);
        pivot++;
        successeur--;
    }

    return true;
}
