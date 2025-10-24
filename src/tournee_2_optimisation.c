/*
 * tournee_2_optimisation.c
 */

#include "tournee_2_optimisation.h"
#include "traitement_interruption.h"
#include "calcul_distance.h"

#include <stdlib.h>
#include <time.h>

#define DIFFERENCE_MINIMALE 1e-9

Resultat tournee_plus_proche_voisin(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);

    for (size_t sommet_fixe = 0; sommet_fixe < nombre_points - 1; sommet_fixe++)
    {
        size_t voisin_plus_proche = sommet_fixe + 1;
        distance distance_minimale = matrice_obtenir_distance(matrice, permutation_obtenir_sommet(permutation, sommet_fixe), permutation_obtenir_sommet(permutation, voisin_plus_proche));

        for (size_t voisin = sommet_fixe + 1; voisin < nombre_points; voisin++)
        {
            distance distance_calculee = matrice_obtenir_distance(matrice, permutation_obtenir_sommet(permutation, sommet_fixe), permutation_obtenir_sommet(permutation, voisin));

            if (distance_calculee < distance_minimale)
            {
                voisin_plus_proche = voisin;
                distance_minimale = distance_calculee;
            }
        }

        permutation_echanger_sommets(permutation, sommet_fixe + 1, voisin_plus_proche);
    }

    Resultat resultat;
    resultat.permutation = permutation;
    resultat.longueur = permutation_calculer_distance_totale(resultat.permutation, matrice);

    return resultat;
}

/* Donne un nombre aléatoire compris entre borne_inf et borne_sup exclus.
 * borne_inf <= nombre_aleatoire < borne_sup */
size_t donner_nombre_aleatoire(size_t borne_inf, size_t borne_sup)
{
    return borne_inf + rand() % (borne_sup - borne_inf);
}

Resultat tournee_marche_aleatoire(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points);

    for (size_t sommet = 0; sommet < nombre_points - 1; sommet++)
    {
        size_t voisin = donner_nombre_aleatoire(sommet, nombre_points);

        permutation_echanger_sommets(permutation, sommet, voisin);
    }

    Resultat resultat;
    resultat.permutation = permutation;
    resultat.longueur = permutation_calculer_distance_totale(resultat.permutation, matrice);

    return resultat;
}

Resultat tournee_2_optimisation(MatriceDistance matrice, Permutation permutation)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    distance longueur = permutation_calculer_distance_totale(permutation, matrice);

    size_t nombre_permutations_traitees = 1;

    bool amelioration_trouvee = true;
    bool demande_stop = false;

    while (amelioration_trouvee && !demande_stop)
    {
        amelioration_trouvee = false;

        for (size_t sommet_A = 0; sommet_A < nombre_points - 1; sommet_A++)
        {
            for (size_t sommet_B = sommet_A + 1; sommet_B < nombre_points; sommet_B++)
            {
                nombre_permutations_traitees++;

                distance difference = permutation_difference_apres_decroisement(matrice, permutation, sommet_A, sommet_B);

                if (interruption)
                {
                    demande_stop = interruption_traitement(permutation, permutation, longueur);
                }
                if (demande_stop)
                {
                    break;
                }

                if (difference < -DIFFERENCE_MINIMALE)
                {
                    permutation_echanger_aretes(permutation, sommet_A, sommet_B);
                    longueur += difference;
                    amelioration_trouvee = true;
                    break;
                }
            }

            if (amelioration_trouvee || demande_stop)
            {
                break;
            }
        }
    }

    Resultat resultat;
    resultat.permutation = permutation;
    resultat.longueur = longueur;

    return resultat;
}

Resultat tournee_2_optimisation_plus_proche_voisin(MatriceDistance matrice)
{
    Permutation permutation = tournee_plus_proche_voisin(matrice).permutation;

    return tournee_2_optimisation(matrice, permutation);
}

Resultat tournee_2_optimisation_marche_aleatoire(MatriceDistance matrice)
{
    Permutation permutation = tournee_marche_aleatoire(matrice).permutation;

    return tournee_2_optimisation(matrice, permutation);
}
