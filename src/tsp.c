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
        traitement(sortie, options.nom_fichier_entree, CANONIQUE, matrice);
    }
    switch (options.methode_calcul)
    {
    case BF:
        traitement(sortie, options.nom_fichier_entree, BF, matrice);
        break;
    case NN:
        traitement(sortie, options.nom_fichier_entree, NN, matrice);
        break;
    case RW:
        traitement(sortie, options.nom_fichier_entree, RW, matrice);
        break;
    case NN2OPT:
        traitement(sortie, options.nom_fichier_entree, NN2OPT, matrice);
        break;
    case RW2OPT:
        traitement(sortie, options.nom_fichier_entree, RW2OPT, matrice);
        break;
    case GA:
        traitement(sortie, options.nom_fichier_entree, GA, matrice);
        break;
    case GADPX:
        traitement(sortie, options.nom_fichier_entree, GADPX, matrice);
        break;
    case ALL:
        traitement(sortie, options.nom_fichier_entree, NN, matrice);
        traitement(sortie, options.nom_fichier_entree, RW, matrice);
        traitement(sortie, options.nom_fichier_entree, NN2OPT, matrice);
        traitement(sortie, options.nom_fichier_entree, RW2OPT, matrice);
        traitement(sortie, options.nom_fichier_entree, GA, matrice);
        traitement(sortie, options.nom_fichier_entree, GADPX, matrice);
        break;
    default:
        break;
    }

    supprimer_matrice(&matrice);

    fermeture_entree(entree, options);
    fermeture_sortie(sortie, options);

    exit(EXIT_SUCCESS);
}
