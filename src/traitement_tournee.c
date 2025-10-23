/*
 * traitement_tournee.c
 */

#include "traitement_tournee.h"
#include "affichage.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"
#include "traitement_interruption.h"

#include <time.h>
#include <math.h>

void tournee_gestionnaire(FILE *sortie, char *nom_fichier_entree, MatriceDistance matrice, MethodeCalcul methode, AlgorithmeTournee calculer_tournee)
{
    clock_t temps = clock();

    signal(SIGINT, interruption_gestionnaire);
    Resultat resultat = calculer_tournee(matrice);
    signal(SIGINT, SIG_DFL);

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, nom_fichier_entree, methode, temps_total, resultat.distance, resultat.permutation);

    permutation_supprimer(&resultat.permutation);
}

void tournee_traitement(FILE *sortie, Options options, MatriceDistance matrice)
{
    afficher_noms_champs(sortie);

    if (options.canonique)
    {
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, CANONIQUE, &tournee_canonique);
    }

    switch (options.methode_calcul)
    {
    case BF:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, BF, &tournee_force_brute_naive);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, BF, &tournee_force_brute_elagage);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, BF, &tournee_force_brute_incrementale);
        break;

    case NN:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, NN, &tournee_canonique);
        break;

    case RW:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, RW, &tournee_canonique);
        break;

    case NN2OPT:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, NN2OPT, &tournee_canonique);
        break;

    case RW2OPT:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, RW2OPT, &tournee_canonique);
        break;

    case GA:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, GA, &tournee_canonique);
        break;

    case GADPX:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, GADPX, &tournee_canonique);
        break;

    case ALL:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, NN, &tournee_canonique);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, RW, &tournee_canonique);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, NN2OPT, &tournee_canonique);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, RW2OPT, &tournee_canonique);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, GA, &tournee_canonique);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, GADPX, &tournee_canonique);
        break;

    default:
        break;
    }
}
