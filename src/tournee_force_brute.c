/*
 * tournee_force_brute.c
 */

#include "tournee_force_brute.h"
#include "structure_permutation.h"
#include "affichage.h"

Resultat calcul_tournee_force_brute(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);
    Permutation permutation_minimale = permutation_creer(nombre_points);

    distance longueur = permutation_calculer_distance_totale(permutation, matrice);
    distance longueur_minimale = longueur;

    while (permutation_avancer(permutation))
    {
        longueur = permutation_calculer_distance_totale_rapide(permutation, matrice, longueur_minimale);

        if (longueur < longueur_minimale)
        {
            longueur_minimale = longueur;
            permutation_copier(permutation_minimale, permutation);
        }
    }

    permutation_supprimer(&permutation);

    Resultat resultat;

    resultat.permutation = permutation_minimale;
    resultat.distance = longueur_minimale;

    return resultat;
}
