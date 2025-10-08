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
#include "force_brute.h"
#include "2_optimisation.h"
#include "genetique.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

/* Exemple d'utilisation :
 * make
 * /bin/tsp -f data/pr76.tsp -m bf -o bin/tsp.txt -c */

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

    MatriceDistances matrice = creer_matrice(tableau_points, specification.calculer_distance);
    remplir_matrice(matrice);
    afficher_matrice(sortie, matrice);

    if (options.est_donne_canonique)
    {
        TableauDistances tournee = tournee_canonique(matrice);
        afficher_tournee(sortie, tournee);

        distance somme = somme_tableau_distances(tournee);
        fprintf(sortie, "Distance totale : %lf\n", somme);

        supprimer_tableau_distances(&tournee);
    }

    supprimer_matrice(&matrice);

    fermeture_entree(entree, options);
    fermeture_sortie(sortie, options);

    exit(EXIT_SUCCESS);
}
