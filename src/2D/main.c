/*
 * main.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "calcul_distance.h"
#include "lecture_tsp.h"
#include "options.h"
#include "traitement_tournee.h"
#include "traitement_interruption.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL)); /* Initialisation de la graine pour la génération de nombres aléatoires. */

    arguments = options_traiter_arguments(argc, argv);

    fichier_ouvrir_entree(arguments);
    fichier_ouvrir_sortie(arguments);

    Specification specification = lecture_tsp_lire_specification(entree);

    matrice = matrice_creer(
        specification.nombre_points, sizeof(Point), sizeof(distance),
        specification.distance_calculer, &distance_additionner, &distance_soustraire, &distance_comparer);

    lecture_tsp_lire_points(entree, matrice);

    matrice_remplir(matrice);

    tournee_traiter_methode(sortie, arguments, matrice);

    matrice_supprimer(&matrice);

    fichier_fermer_entree(arguments);
    fichier_fermer_sortie(arguments);

    exit(EXIT_SUCCESS);
}
