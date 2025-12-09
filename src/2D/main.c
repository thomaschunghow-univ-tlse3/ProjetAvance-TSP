/*
 * main.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "affichage.h"
#include "calcul_distance.h"
#include "lecture_tsp.h"
#include "options.h"
#include "traitement_interruption.h"
#include "traitement_tournee.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL)); /* Initialisation de la graine pour la génération de nombres aléatoires. */

    global_arguments = options_traiter_arguments(argc, argv);

    fichier_ouvrir_entree_tsp(global_arguments);
    fichier_ouvrir_sortie(global_arguments);

    Specification specification = lecture_tsp_lire_specification(entree);

    global_matrice =
        matrice_creer(specification.nombre_points, sizeof(Point), sizeof(distance), specification.distance_calculer,
                      &distance_additionner, &distance_soustraire, &distance_comparer);

    lecture_tsp_lire_points(entree, global_matrice);

    matrice_remplir(global_matrice);

#ifndef COMPARAISON_RESULTAT
    tournee_traiter_methode(sortie, global_arguments, global_matrice);
#endif // COMPARAISON_RESULTAT

    fichier_fermer_entree(global_arguments);

#ifdef COMPARAISON_RESULTAT
    fichier_ouvrir_entree_tour(global_arguments);

    Permutation meilleure_tournee = permutation_creer(matrice_obtenir_nombre_points(global_matrice),
                                                      matrice_obtenir_taille_distance(global_matrice));

    lecture_tour_lire_points(entree, meilleure_tournee);

    permutation_calculer_longueur(meilleure_tournee, global_matrice);

    fprintf(sortie, "Instance ; Longueur ; Tour\n");
    fprintf(sortie, "%-25s ; ", global_arguments.nom_fichier_entree);

    afficher_longueur(sortie, meilleure_tournee);
    fprintf(sortie, " ; ");

    afficher_permutation(sortie, meilleure_tournee, 0);
    fprintf(sortie, "\n");

    permutation_supprimer(&meilleure_tournee);

    fichier_fermer_entree(global_arguments);
#endif // COMPARAISON_RESULTAT

    matrice_supprimer(&global_matrice);

    fichier_fermer_sortie(global_arguments);

    exit(EXIT_SUCCESS);
}
