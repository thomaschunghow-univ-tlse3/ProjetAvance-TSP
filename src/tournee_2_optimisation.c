/*
 * tournee_2_optimisation.c
 */

#include "tournee_2_optimisation.h"
#include "traitement_interruption.h"

#include <stdlib.h>
#include <time.h>

Permutation tournee_plus_proche_voisin(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));

    for (size_t sommet_fixe = 0; sommet_fixe < nombre_points - 1; sommet_fixe++)
    {
        size_t valeur_sommet_fixe = permutation_obtenir_sommet(permutation, sommet_fixe);

        size_t voisin_plus_proche = sommet_fixe + 1;
        size_t valeur_voisin_plus_proche = permutation_obtenir_sommet(permutation, voisin_plus_proche);

        for (size_t voisin = sommet_fixe + 2; voisin < nombre_points; voisin++)
        {
            size_t valeur_voisin = permutation_obtenir_sommet(permutation, voisin);

            if (matrice_comparer_distances(matrice, valeur_sommet_fixe, valeur_voisin, valeur_sommet_fixe, valeur_voisin_plus_proche) < 0)
            {
                voisin_plus_proche = voisin;
                valeur_voisin_plus_proche = valeur_voisin;
            }
        }

        permutation_echanger_sommets(permutation, sommet_fixe + 1, voisin_plus_proche);
    }

    permutation_calculer_longueur(permutation, matrice);

    return permutation;
}

Permutation tournee_marche_aleatoire(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));

    permutation_melanger(permutation);

    permutation_calculer_longueur(permutation, matrice);

    return permutation;
}

Permutation tournee_2_optimisation(MatriceDistance matrice, Permutation permutation)
{
#ifdef AFFICHAGE_INTERACTIF
    fprintf(sortie_interactive, "2-optimisation\n");
#endif // AFFICHAGE_INTERACTIF

    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    permutation_calculer_longueur(permutation, matrice);

    Permutation permutation_decroisee = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));

    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    bool amelioration_trouvee = true;
    bool demande_stop = false;

    while (amelioration_trouvee && !demande_stop)
    {
        amelioration_trouvee = false;

        permutation_copier(permutation_decroisee, permutation);

#ifdef AFFICHAGE_INTERACTIF
        afficher_permutation(sortie_interactive, permutation, 0);
        fprintf(sortie_interactive, "\n");
#endif // AFFICHAGE_INTERACTIF

        for (size_t sommet_A = 0; sommet_A < nombre_points - 1; sommet_A++)
        {
            for (size_t sommet_B = sommet_A + 1; sommet_B < nombre_points; sommet_B++)
            {
                permutation_calculer_difference_apres_decroisement(
                    matrice, permutation, sommet_A, sommet_B, permutation_decroisee);

                /* Gestion des interruptions. */
                if (interruption)
                {
                    demande_stop = interruption_traiter_signal(permutation, permutation_decroisee);
                }
                if (demande_stop)
                {
                    break;
                }

                if (permutation_comparer_longueurs(permutation_decroisee, permutation, distance_comparer) < 0)
                {
                    amelioration_trouvee = true;
                    permutation_echanger_aretes(permutation, sommet_A, sommet_B);
                    break;
                }
            }

            if (amelioration_trouvee || demande_stop)
            {
                break;
            }
        }
    }

    return permutation;
}

Permutation tournee_2_optimisation_plus_proche_voisin(MatriceDistance matrice)
{
    Permutation permutation = tournee_plus_proche_voisin(matrice);

    return tournee_2_optimisation(matrice, permutation);
}

Permutation tournee_2_optimisation_marche_aleatoire(MatriceDistance matrice)
{
    Permutation permutation = tournee_marche_aleatoire(matrice);

    return tournee_2_optimisation(matrice, permutation);
}
