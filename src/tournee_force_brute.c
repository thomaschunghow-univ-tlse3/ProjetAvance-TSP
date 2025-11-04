/*
 * tournee_force_brute.c
 */

#include "tournee_force_brute.h"
#include "traitement_interruption.h"
#include "structure_permutation.h"
#include "affichage.h"
#include "calcul_distance.h"

Resultat tournee_force_brute_naive(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);
    Permutation permutation_minimale = permutation_creer(nombre_points);

    distance longueur = permutation_calculer_distance_totale(permutation, matrice);
    distance longueur_minimale = longueur;

    bool demande_stop = false;

    while (permutation_avancer(permutation) && !demande_stop)
    {
        longueur = permutation_calculer_distance_totale(permutation, matrice);

        if (longueur < longueur_minimale)
        {
            longueur_minimale = longueur;
            permutation_copier(permutation_minimale, permutation);
        }

        if (interruption)
        {
            demande_stop = interruption_traitement(permutation, permutation_minimale, longueur_minimale);
        }
    }

    permutation_supprimer(&permutation);

    Resultat resultat;
    resultat.permutation = permutation_minimale;
    resultat.longueur = longueur_minimale;

    return resultat;
}

Resultat tournee_force_brute_elagage(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);
    Permutation permutation_minimale = permutation_creer(nombre_points);

    distance longueur = permutation_calculer_distance_totale(permutation, matrice);
    distance longueur_minimale = longueur;

    bool demande_stop = false;

    while (permutation_avancer(permutation) && !demande_stop)
    {
        longueur = permutation_calculer_distance_totale_avec_elagage(permutation, matrice, longueur_minimale);

        if (longueur < longueur_minimale)
        {
            longueur_minimale = longueur;
            permutation_copier(permutation_minimale, permutation);
        }

        if (interruption)
        {
            demande_stop = interruption_traitement(permutation, permutation_minimale, longueur_minimale);
        }
    }

    permutation_supprimer(&permutation);

    Resultat resultat;
    resultat.permutation = permutation_minimale;
    resultat.longueur = longueur_minimale;

    return resultat;
}

Resultat tournee_force_brute_incrementale(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);
    Permutation permutation_minimale = permutation_creer(nombre_points);

    distance longueur = permutation_calculer_distance_totale(permutation, matrice);
    distance longueur_minimale = longueur;

    bool demande_stop = false;

    while (permutation_avancer_et_incrementer_longueur(permutation, matrice, &longueur) && !demande_stop)
    {

        if (longueur < longueur_minimale)
        {
            longueur_minimale = longueur;
            permutation_copier(permutation_minimale, permutation);
        }

        if (interruption)
        {
            demande_stop = interruption_traitement(permutation, permutation_minimale, longueur_minimale);
        }
    }

    permutation_supprimer(&permutation);

    Resultat resultat;
    resultat.permutation = permutation_minimale;
    resultat.longueur = longueur_minimale;

    return resultat;
}
