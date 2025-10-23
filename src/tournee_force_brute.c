/*
 * tournee_force_brute.c
 */

#include "traitement_interruption.h"
#include "tournee_force_brute.h"
#include "structure_permutation.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stddef.h>
#include <signal.h>

// fonction auxiliere qui copie un tab d'indices dans un TAD Permutation
void copier_tableau(Permutation permutation, size_t *tabIndices)
{
    for (size_t i = 0; i < nombre_indices(permutation); i++)
    {
        permutation->indices[i] = tabIndices[i];
    }
}

Resultat calcul_tournee_force_brute_elagage(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);
    Permutation permutation_minimale = permutation_creer(nombre_points);

    distance longueur = permutation_calculer_distance_totale(permutation, matrice);
    distance longueur_minimale = longueur;

    while (permutation_avancer(permutation))
    {
        longueur = permutation_calculer_distance_totale_avec_elagage(permutation, matrice, longueur_minimale);

        while (permutation_suivante(permutation_courante) && !stop)
        {

            d_courante = distance_totale_permutation(permutation_courante, matrice);

            if (premiere_permutation)
            {
                d_minimale = d_courante;
                d_maximal = d_courante;
                copier_tableau(meilleure_permutation, tableau_indices(permutation_courante));
                premiere_permutation = false;
            }
        }

        if (flag)
        {
            gerer_interruption_bf(d_courante, d_minimale, meilleure_permutation, permutation_courante, &stop);
        }

        if (d_courante < d_minimale)
        {
            d_minimale = d_courante;
            copier_tableau(meilleure_permutation, tableau_indices(permutation_courante));
        }

        if (d_courante > d_maximal)
        {
            d_maximal = d_courante;
        }
    }

    supprimer_permutation(&permutation_courante);
    signal(SIGINT, SIG_DFL);

    Resultat resultat_final;
    resultat_final.permutation = meilleure_permutation;
    resultat_final.distance = d_minimale;

    return resultat_final;
}

Resultat calcul_tournee_force_brute_incrementale(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);
    Permutation permutation_minimale = permutation_creer(nombre_points);

    distance longueur = permutation_calculer_distance_totale(permutation, matrice);
    distance longueur_minimale = longueur;

    while (permutation_avancer_et_incrementer_longueur(permutation, matrice, &longueur))
    {
        if (longueur < longueur_minimale)
        {
            longueur_minimale = longueur;
            permutation_copier(permutation_minimale, permutation);
        }
    }

    if (longueur < longueur_minimale)
    {
        longueur_minimale = longueur;
        permutation_copier(permutation_minimale, permutation);
    }

    permutation_supprimer(&permutation);

    Resultat resultat;

    resultat.permutation = permutation_minimale;
    resultat.distance = longueur_minimale;

    return resultat;
}
