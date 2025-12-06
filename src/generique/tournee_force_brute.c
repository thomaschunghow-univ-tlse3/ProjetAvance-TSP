/*
 * tournee_force_brute.c
 */

#include "tournee_force_brute.h"

#include "structure_matrice.h"
#include "structure_permutation.h"

#include <stdbool.h>
#include <stdlib.h>

void tournee_force_brute_naive(MatriceDistance matrice, Permutation permutation_courante, Permutation permutation_minimale)
{
    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    permutation_initialiser(permutation_courante);
    permutation_calculer_longueur(permutation_courante, matrice);
    permutation_copier(permutation_minimale, permutation_courante);

    while (permutation_avancer(permutation_courante))
    {
        permutation_calculer_longueur(permutation_courante, matrice);

        if (permutation_comparer_longueurs(permutation_courante, permutation_minimale, distance_comparer) < 0)
        {
            permutation_copier(permutation_minimale, permutation_courante);
        }
    }
}

void tournee_force_brute_avec_elagage(MatriceDistance matrice, Permutation permutation_courante, Permutation permutation_minimale)
{
    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    permutation_initialiser(permutation_courante);
    permutation_calculer_longueur(permutation_courante, matrice);
    permutation_copier(permutation_minimale, permutation_courante);

    while (permutation_avancer(permutation_courante))
    {
        permutation_calculer_longueur_avec_elagage(permutation_courante, matrice, permutation_minimale);

        if (permutation_comparer_longueurs(permutation_courante, permutation_minimale, distance_comparer) < 0)
        {
            permutation_copier(permutation_minimale, permutation_courante);
        }
    }
}

void tournee_force_brute_incrementale(MatriceDistance matrice, Permutation permutation_courante, Permutation permutation_minimale)
{
    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    permutation_initialiser(permutation_courante);
    permutation_calculer_longueur(permutation_courante, matrice);
    permutation_copier(permutation_minimale, permutation_courante);

    while (permutation_avancer_et_incrementer_longueur(permutation_courante, matrice))
    {
        if (permutation_comparer_longueurs(permutation_courante, permutation_minimale, distance_comparer) < 0)
        {
            permutation_copier(permutation_minimale, permutation_courante);
        }
    }
}
