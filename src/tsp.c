/*
 * tsp.c
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "structures_de_donnees.h"
#include "calcul_distance.h"
#include "lecture_donnees.h"
#include "affichage.h"
#include "traitement_options.h"
#include "canonique.h"

#include <stdio.h>
#include <stdlib.h>

/* Exemple d'utilisation : /bin/tsp -f data/pr76.tsp -m bf -o bin/tsp.txt */

int main(int argc, char **argv)
{
    Options options = traitement_options(argc, argv);

    FILE *entree = ouverture_entree(options);
    FILE *sortie = ouverture_sortie(options);

    Specification specification = lire_specification_tsp(entree);
    afficher_specification(sortie, specification);

    TableauPoints tableau_points = creer_tableau_points(specification.nombre_points);
    lire_points_tsp(entree, tableau_points);
    afficher_tableau_points(sortie, tableau_points);

    MatriceDistances matrice = creer_matrice(tableau_points, calculer_distance_euclidienne);
    remplir_matrice(matrice);
    afficher_matrice(sortie, matrice);

    TableauDistances tournee = tournee_canonique(matrice);
    afficher_tournee(sortie, tournee);

    distance somme = somme_tableau_distances(tournee);
    fprintf(sortie, "Distance totale : %lf\n", somme);

    supprimer_matrice(&matrice);
    supprimer_tableau_distances(&tournee);

    fermeture_entree(entree, options);
    fermeture_sortie(sortie, options);

    exit(EXIT_SUCCESS);
}
