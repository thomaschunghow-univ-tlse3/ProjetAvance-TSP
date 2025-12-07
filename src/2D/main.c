/*
 * main.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

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

    fichier_ouvrir_entree(global_arguments);
    fichier_ouvrir_sortie(global_arguments);

    Specification specification = lecture_tsp_lire_specification(entree);

    global_matrice =
        matrice_creer(specification.nombre_points, sizeof(Point), sizeof(distance), specification.distance_calculer,
                      &distance_additionner, &distance_soustraire, &distance_comparer);

    lecture_tsp_lire_points(entree, global_matrice);

    matrice_remplir(global_matrice);

    tournee_traiter_methode(sortie, global_arguments, global_matrice);

    matrice_supprimer(&global_matrice);

    fichier_fermer_entree(global_arguments);
    fichier_fermer_sortie(global_arguments);

    exit(EXIT_SUCCESS);
}
