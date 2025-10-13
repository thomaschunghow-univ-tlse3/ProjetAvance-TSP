/*
 *
 * Programme principal pour la résolution du problème du voyageur de commerce.
 */

#include "structures_permutations.h"
#include "traitement_lecture_donnees.h"
#include "affichage.h"
#include "traitement_options.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"
#include "tournee_2_optimisation.h"
#include "tournee_genetique.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

/* Exemple d'utilisation :
 * make
 * ./bin/tsp -f data/pr76.tsp -m bf -o bin/tsp.txt -c */

int main(int argc, char **argv)
{
    Options options = traitement_options(argc, argv);

    FILE *entree = ouverture_entree(options);
    FILE *sortie = ouverture_sortie(options);

    Specification specification = lire_specification_tsp(entree);

    TableauPoints tableau_points = creer_tableau_points(specification.nombre_points);
    lire_points_tsp(entree, tableau_points);

    MatriceDistances matrice = creer_matrice(tableau_points, specification.calculer_distance);

    afficher_noms_champs(sortie);

    if (options.est_donne_canonique)
    {
        // traitement(sortie, &calcul_tournee_canonique, options, matrice);
    }
    switch (options.methode_calcul)
    {
    case BF:
        // traitement_bf(sortie, matrice);
        break;
    case NN:
        break;
    case RW:
        break;
    case NN2OPT:
        break;
    case RW2OPT:
        break;
    case GA:
        break;
    case GADPX:
        break;
    case ALL:
        break;
    }

    supprimer_matrice(&matrice);

    fermeture_entree(entree, options);
    fermeture_sortie(sortie, options);

    exit(EXIT_SUCCESS);
}
