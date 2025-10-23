/*
 * main.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "affichage.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"
#include "tournee_2_optimisation.h"
#include "tournee_genetique.h"

#include <stdlib.h>

/* Exemple d'utilisation :
 * make
 * ./bin/main -f data/tsp/pr76.tsp -m bf -o bin/resultat.txt -c
 * ./bin/main -f data/tsp/att10.tsp -m bf -c
 * python3 ./test/test_tsp_c.py
 *
 * Pour générer la documentation :
 * doxygen Doxyfile */

int main(int argc, char **argv)
{
    Options options = options_traitement(argc, argv);

    FILE *entree = ouverture_entree(options);
    FILE *sortie = ouverture_sortie(options);

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
