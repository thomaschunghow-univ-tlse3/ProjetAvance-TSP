/*
 */

#include "structures_permutations.h"

#include <stdio.h>
#include <stdlib.h>

Permutation creer_permutation(size_t nombre_indices)
{
    Permutation permutation = malloc(sizeof(Permutation) + nombre_indices * sizeof(size_t));
    permutation->nombre_indices = nombre_indices;
    permutation->indices = (size_t *)permutation + 1;
    for (size_t i = 0; i < nombre_indices; i++)
    {
        (permutation->indices)[i] = i;
    }
    return permutation;
}

void verifier_permutation_non_vide(Permutation permutation)
{
    if (permutation == NULL)
    {
        fprintf(stderr,
                "Erreur verifier_permutation_non_vide :\n"
                "Permutation vide.\n");
        exit(EXIT_FAILURE);
    }
}

void supprimer_permutation(Permutation *permutation)
{
    verifier_permutation_non_vide(*permutation);
    free(*permutation);
    *permutation = NULL;
}

void echanger_indices(Permutation permutation, int i, int j)
{
    size_t temp = permutation->indices[i];
    permutation->indices[i] = permutation->indices[j];
    permutation->indices[j] = temp;
}

distance distance_totale_permutation(Permutation permutation, MatriceDistances matrice)
{
    distance distance_totale = 0;
    for (size_t i = 0; i < permutation->nombre_indices - 1; i++)
    {
        distance_totale += *obtenir_distance_matrice(matrice, permutation->indices[i], permutation->indices[i + 1]);
    }
    return distance_totale;
}
