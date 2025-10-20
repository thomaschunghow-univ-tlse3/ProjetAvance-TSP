/*
 */

#include "structures_permutations.h"

#include <stdio.h>
#include <stdlib.h>

Permutation creer_permutation(size_t nombre_indices)
{
    Permutation permutation = malloc(sizeof(struct permutation) + nombre_indices * sizeof(size_t));
    if (permutation == NULL)
    {
        printf("DEBUG\n");
        fprintf(stderr,
                "Erreur creer_permutation :\n"
                "Echec de l'allocation mémoire de la permutation.\n");
        exit(EXIT_FAILURE);
    }
    permutation->nombre_indices = nombre_indices;
    permutation->indices = (size_t *)(permutation + 1);
    for (size_t i = 0; i < nombre_indices; i++)
    {
        permutation->indices[i] = i;
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

size_t nombre_indices(Permutation permutation)
{
    verifier_permutation_non_vide(permutation);
    return permutation->nombre_indices;
}

size_t *tableau_indices(Permutation permutation)
{
    verifier_permutation_non_vide(permutation);
    return permutation->indices;
}

TableauPoints transformer_permutation_en_points(Permutation permutation)
{
    verifier_permutation_non_vide(permutation);
    return creer_tableau_points(permutation->nombre_indices);
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
    distance_totale += *obtenir_distance_matrice(matrice, permutation->indices[0], permutation->indices[permutation->nombre_indices - 1]);
    return distance_totale;
}

/*
 * calcule la permutation suivante de l'ordre lexicographique
 * et renvoie un boolean qui montre si la permutation suivante existe
 */
bool permutation_suivante(Permutation permutation)
{
    // trouver le suffix non croissant
    if (permutation->nombre_indices == 0)
        return false;
    size_t i = permutation->nombre_indices - 1;
    while (i > 1 && (permutation->indices)[i - 1] >= (permutation->indices)[i])
        i--;
    if (i == 1) // 1 au lieu de 0 parcequ'on commence toujours par le meme point
        return false;

    // trouver le successeur du pivot
    size_t j = permutation->nombre_indices - 1;
    while ((permutation->indices)[j] <= (permutation->indices)[i - 1])
        j--;

    echanger_indices(permutation, i - 1, j);

    // inverser le suffix
    j = permutation->nombre_indices - 1;
    while (i < j)
    {
        echanger_indices(permutation, i, j);
        i++;
        j--;
    }
    return true;
}
