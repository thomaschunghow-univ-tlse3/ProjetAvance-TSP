/*
 * tournee_2_optimisation.c
 */

#include "tournee_2_optimisation.h"

#include "structure_matrice.h"
#include "structure_permutation.h"

#include <stdlib.h>

#ifdef AFFICHAGE_INTERACTIF_2_OPT
#include "affichage.h"
#include "options.h"

#include <stdio.h>
#endif // AFFICHAGE_INTERACTIF_2_OPT

void tournee_plus_proche_voisin(MatriceDistance matrice, Permutation permutation_resultat)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    for (size_t sommet_fixe = 0; sommet_fixe < nombre_points - 1; sommet_fixe++)
    {
        size_t valeur_sommet_fixe = permutation_obtenir_sommet(permutation_resultat, sommet_fixe);

        size_t voisin_plus_proche = sommet_fixe + 1;
        size_t valeur_voisin_plus_proche = permutation_obtenir_sommet(permutation_resultat, voisin_plus_proche);

        for (size_t voisin = sommet_fixe + 2; voisin < nombre_points; voisin++)
        {
            size_t valeur_voisin = permutation_obtenir_sommet(permutation_resultat, voisin);

            if (matrice_comparer_distances(matrice, valeur_sommet_fixe, valeur_voisin, valeur_sommet_fixe, valeur_voisin_plus_proche) < 0)
            {
                voisin_plus_proche = voisin;
                valeur_voisin_plus_proche = valeur_voisin;
            }
        }

        permutation_echanger_sommets(permutation_resultat, sommet_fixe + 1, voisin_plus_proche);
    }

    permutation_calculer_longueur(permutation_resultat, matrice);
}

void tournee_marche_aleatoire(MatriceDistance matrice, Permutation permutation_resultat)
{
    permutation_melanger(permutation_resultat);

    permutation_calculer_longueur(permutation_resultat, matrice);
}

void tournee_2_optimisation(MatriceDistance matrice, Permutation permutation_courante, Permutation permutation_resultat)
{
#ifdef AFFICHAGE_INTERACTIF_2_OPT
    fprintf(sortie, "2-optimisation\n");
#endif // AFFICHAGE_INTERACTIF_2_OPT

    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    permutation_calculer_longueur(permutation_resultat, matrice);

    bool amelioration_trouvee = true;

    while (amelioration_trouvee)
    {
        amelioration_trouvee = false;

        permutation_copier(permutation_courante, permutation_resultat);

#ifdef AFFICHAGE_INTERACTIF_2_OPT
        afficher_permutation(sortie, permutation, 0);
        fprintf(sortie, "\n");
#endif // AFFICHAGE_INTERACTIF_2_OPT

        for (size_t sommet_A = 0; sommet_A < nombre_points - 1; sommet_A++)
        {
            for (size_t sommet_B = sommet_A + 1; sommet_B < nombre_points; sommet_B++)
            {
                amelioration_trouvee = permutation_decroiser(
                    matrice, permutation_resultat, sommet_A, sommet_B, permutation_courante);

                if (amelioration_trouvee)
                {
                    break;
                }
            }

            if (amelioration_trouvee)
            {
                break;
            }
        }
    }
}

void tournee_2_optimisation_plus_proche_voisin(MatriceDistance matrice, Permutation permutation_courante, Permutation permutation_resultat)
{
    tournee_plus_proche_voisin(matrice, permutation_resultat);

    tournee_2_optimisation(matrice, permutation_courante, permutation_resultat);
}

void tournee_2_optimisation_marche_aleatoire(MatriceDistance matrice, Permutation permutation_courante, Permutation permutation_resultat)
{
    tournee_marche_aleatoire(matrice, permutation_resultat);

    tournee_2_optimisation(matrice, permutation_courante, permutation_resultat);
}
