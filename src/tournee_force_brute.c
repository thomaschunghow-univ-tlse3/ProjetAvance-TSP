/*
 * tournee_force_brute.c
 */

#include "tournee_force_brute.h"
#include "traitement_interruption.h"
#include "structure.h"
#include "affichage.h"
#include "calcul_distance.h"

#include <string.h>

Resultat tournee_force_brute_naive(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    size_t taille_distance = matrice_obtenir_taille_distance(matrice);

    Permutation permutation = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_minimale = permutation_creer(nombre_points, taille_distance);

    void *longueur = malloc(taille_distance);
    permutation_calculer_longueur(permutation, matrice);
    permutation_obtenir_longueur(permutation, &longueur);

    void *longueur_minimale = malloc(taille_distance);
    memcpy(longueur_minimale, longueur, taille_distance);

    bool demande_stop = false;

    while (permutation_avancer(permutation) && !demande_stop)
    {
        permutation_calculer_longueur(permutation, matrice);
        permutation_obtenir_longueur(permutation, &longueur);

        if (longueur < longueur_minimale)
        {
            longueur_minimale = longueur;
            permutation_copier(permutation_minimale, permutation);
        }

        /* Gestion des interruptions. */
        if (interruption)
        {
            demande_stop = interruption_traitement(permutation, permutation_minimale, &longueur_minimale);
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

    Permutation permutation = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));
    Permutation permutation_minimale = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));

    distance longueur;
    permutation_calculer_longueur(permutation, matrice);
    permutation_obtenir_longueur(permutation, &longueur);

    distance longueur_minimale = longueur;

    bool demande_stop = false;

    while (permutation_avancer(permutation) && !demande_stop)
    {
        permutation_calculer_longueur_avec_elagage(permutation, matrice, &longueur_minimale);
        permutation_obtenir_longueur(permutation, &longueur);

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

    Permutation permutation = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));
    Permutation permutation_minimale = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));

    distance longueur;
    permutation_calculer_longueur(permutation, matrice);
    permutation_obtenir_longueur(permutation, &longueur);

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
