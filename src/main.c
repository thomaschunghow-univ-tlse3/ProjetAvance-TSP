/*
 * main.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "structure_permutation.h"
#include "lecture_donnees.h"
#include "affichage.h"
#include "options.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"
#include "tournee_2_optimisation.h"
#include "tournee_genetique.h"

#include <stdlib.h>

/* Exemple d'utilisation :
 * make
 * ./bin/main -f data/pr76.tsp -m bf -o bin/resultat.txt -c
 * ./bin/main -f data/att10.tsp -m bf -c */

int main(int argc, char **argv)
{
    Options options = traitement_options(argc, argv);

    FILE *entree = ouverture_entree(options);
    FILE *sortie = ouverture_sortie(options);

    Specification specification = lire_specification_tsp(entree);

    MatriceDistance matrice = matrice_creer(specification.nombre_points, specification.calculer_distance);
	
	//recherche_croisement(matrice,parcours_tableau);
	
    lire_points_tsp(entree, matrice_obtenir_tableau_point(matrice));

    matrice_remplir_distance(matrice);
	
    traitement_tournee(sortie, options, matrice);

    matrice_supprimer(&matrice);

    fermeture_entree(entree, options);
    fermeture_sortie(sortie, options);

    exit(EXIT_SUCCESS);
}
