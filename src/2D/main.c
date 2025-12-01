/*
 * main.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "calcul_distance.h"
#include "lecture_tsp.h"
#include "options.h"
#include "traitement_tournee.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    Arguments options = options_traiter_arguments(argc, argv);

    fichier_ouvrir_entree(options);
    fichier_ouvrir_sortie(options);

    Specification specification = lecture_tsp_lire_specification(entree);

    MatriceDistance matrice = matrice_creer(
        specification.nombre_points, sizeof(Point), sizeof(distance),
        specification.distance_calculer, &distance_additionner, &distance_soustraire, &distance_comparer);

    lecture_tsp_lire_points(entree, matrice);

    matrice_remplir(matrice);

    tournee_traitement(sortie, options, matrice);

    matrice_supprimer(&matrice);

    fichier_fermer_entree(options);
    fichier_fermer_sortie(options);

    exit(EXIT_SUCCESS);
}
