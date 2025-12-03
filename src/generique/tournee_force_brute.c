/*
 * tournee_force_brute.c
 */

#include "tournee_force_brute.h"

#include "structure_matrice.h"
#include "structure_permutation.h"
#include "traitement_interruption.h"

#include <stdbool.h>
#include <stdlib.h>

Permutation tournee_force_brute_naive(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    size_t taille_distance = matrice_obtenir_taille_distance(matrice);
    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    Permutation permutation = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_minimale = permutation_creer(nombre_points, taille_distance);

    permutation_calculer_longueur(permutation, matrice);
    permutation_copier(permutation_minimale, permutation);

    bool demande_stop = false;

    while (permutation_avancer(permutation) && !demande_stop)
    {
        permutation_calculer_longueur(permutation, matrice);

        if (permutation_comparer_longueurs(permutation, permutation_minimale, distance_comparer) < 0)
        {
            permutation_copier(permutation_minimale, permutation);
        }

        /* Gestion des interruptions. */
        if (interruption)
        {
            demande_stop = interruption_traiter_signal(permutation, permutation_minimale);
        }
    }

    permutation_supprimer(&permutation);

    return permutation_minimale;
}

Permutation tournee_force_brute_avec_elagage(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    size_t taille_distance = matrice_obtenir_taille_distance(matrice);
    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    Permutation permutation = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_minimale = permutation_creer(nombre_points, taille_distance);

    permutation_calculer_longueur(permutation, matrice);
    permutation_copier(permutation_minimale, permutation);

    bool demande_stop = false;

    while (permutation_avancer(permutation) && !demande_stop)
    {
        permutation_calculer_longueur_avec_elagage(permutation, matrice, permutation_minimale);

        if (permutation_comparer_longueurs(permutation, permutation_minimale, distance_comparer) < 0)
        {
            permutation_copier(permutation_minimale, permutation);
        }

        if (interruption)
        {
            demande_stop = interruption_traiter_signal(permutation, permutation_minimale);
        }
    }

    permutation_supprimer(&permutation);

    return permutation_minimale;
}

Permutation tournee_force_brute_incrementale(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    size_t taille_distance = matrice_obtenir_taille_distance(matrice);
    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    Permutation permutation = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_minimale = permutation_creer(nombre_points, taille_distance);

    permutation_calculer_longueur(permutation, matrice);
    permutation_copier(permutation_minimale, permutation);

    bool demande_stop = false;

    while (permutation_avancer_et_incrementer_longueur(permutation, matrice) && !demande_stop)
    {
        if (permutation_comparer_longueurs(permutation, permutation_minimale, distance_comparer) < 0)
        {
            permutation_copier(permutation_minimale, permutation);
        }

        if (interruption)
        {
            demande_stop = interruption_traiter_signal(permutation, permutation_minimale);
        }
    }

    permutation_supprimer(&permutation);

    return permutation_minimale;
}
