/*
 * Résolution du problème du voyageur de commerce.
 */

#include "structures_de_donnees.h"
#include "calcul_distance.h"
#include "lecture_donnees.h"
#include "affichage.h"
#include "traitement_options.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    Options options = traitement_options(argc, argv);

    if (!options.est_donne_canonique)
    {
        exit(EXIT_SUCCESS);
    }
    Specification specification = lire_specification_tsp(options.nom_fichier_entree);
    afficher_specification(specification);
    TableauPoints tableau_points = creer_tableau_points(specification.nombre_points);
    lire_points_tsp(options.nom_fichier_entree, tableau_points);
    // afficher_tableau_points(tableau_points);
    exit(EXIT_SUCCESS);
}
