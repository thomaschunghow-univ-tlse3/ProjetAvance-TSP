/*
 */

#include "traitement_tournee.h"
#include "affichage.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"

#include <time.h>
#include <math.h>

AlgorithmeTournee liste_fonctions_traitement[] = {
    &calcul_tournee_canonique,   // TODO : Remplacer par les bonnes fonctions quand c'est implémenté.
    &calcul_tournee_force_brute, // &calcul_tournee_force_brute,
    &calcul_tournee_canonique,   // &calcul_tournee_plus_proche_voisin,
    &calcul_tournee_canonique,   // &calcul_tournee_marche_aleatoire,
    &calcul_tournee_canonique,   // &calcul_tournee_2_optimisation_plus_proche_voisin,
    &calcul_tournee_canonique,   // &calcul_tournee_2_optimisation_marche_aleatoire,
    &calcul_tournee_canonique,   // &calcul_tournee_genetique_generique,
    &calcul_tournee_canonique,   // &calcul_tournee_genetique_dpx,
};

void calcul_tournee(FILE *sortie, Options options, MatriceDistance matrice)
{
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
}

void traitement(FILE *sortie, char *nom_fichier, MethodeCalcul methode, MatriceDistance matrice)
{
    clock_t temps = clock();

    AlgorithmeTournee fonction_traitement = liste_fonctions_traitement[methode];
    Resultat resultat = fonction_traitement(matrice);

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, nom_fichier, methode, temps_total, resultat.distance, resultat.permutation);

    permutation_supprimer(&resultat.permutation);
}
