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
    traitement_options(argc, argv);

    // EXEMPLE
    char *nom_fichier = "data/rat783.tsp";
    Specification specification = lire_specification_tsp(nom_fichier);
    TableauPoints tableau_points = creer_tableau_points(specification.nombre_points);
    lire_points_tsp(nom_fichier, tableau_points);
    MatriceDistances matrice = creer_matrice(tableau_points, calculer_distance_euclidienne);
    remplir_matrice(matrice);
    afficher_specification(specification);
    afficher_liste_points(tableau_points);
    afficher_matrice(matrice);
    supprimer_matrice(&matrice);
    return EXIT_SUCCESS;
}
