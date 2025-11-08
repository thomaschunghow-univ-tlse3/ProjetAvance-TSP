/*
 * main.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "affichage.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"

#ifdef AFFICHAGE_INTERACTIF
#include "affichage_interactif.h"
#endif // AFFICHAGE_INTERACTIF

#include <stdlib.h>

int main(int argc, char **argv)
{
    Options options = options_traitement(argc, argv);

    FILE *entree = ouverture_entree(options);
    FILE *sortie = ouverture_sortie(options);

#ifdef AFFICHAGE_INTERACTIF
    ouverture_sortie_interactive();
#endif // AFFICHAGE_INTERACTIF

    Specification specification = lecture_specification_tsp(entree);

    MatriceDistance matrice = matrice_creer(specification.nombre_points, specification.calculer_distance);

    lecture_points_tsp(entree, matrice_obtenir_tableau_point(matrice));

    matrice_remplir_distance(matrice);

    tournee_traitement(sortie, options, matrice);

    matrice_supprimer(&matrice);

    fermeture_entree(entree, options);
    fermeture_sortie(sortie, options);

    exit(EXIT_SUCCESS);
}
