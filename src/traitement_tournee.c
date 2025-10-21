/*
 * traitement_tournee.c
 */

#include "traitement_tournee.h"
#include "affichage.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"

#include <time.h>
#include <math.h>

void calcul_tournee(FILE *sortie, char *nom_fichier_entree, MatriceDistance matrice, MethodeCalcul methode, AlgorithmeTournee calculer_tournee)
{
    clock_t temps = clock();

    Resultat resultat = calculer_tournee(matrice);

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, nom_fichier_entree, methode, temps_total, resultat.distance, resultat.permutation);

    permutation_supprimer(&resultat.permutation);
}

void traitement_tournee(FILE *sortie, Options options, MatriceDistance matrice)
{
    afficher_noms_champs(sortie);

    if (options.canonique)
    {
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, CANONIQUE, &calcul_tournee_canonique);
    }

    switch (options.methode_calcul)
    {
    case BF:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, BF, &calcul_tournee_force_brute);
        break;

    case NN:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, NN, NULL);
        break;

    case RW:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, RW, NULL);
        break;

    case NN2OPT:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, NN2OPT, NULL);
        break;

    case RW2OPT:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, RW2OPT, NULL);
        break;

    case GA:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, GA, NULL);
        break;

    case GADPX:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, GADPX, NULL);
        break;

    case ALL:
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, NN, NULL);
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, RW, NULL);
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, NN2OPT, NULL);
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, RW2OPT, NULL);
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, GA, NULL);
        calcul_tournee(sortie, options.nom_fichier_entree, matrice, GADPX, NULL);
        break;

    default:
        break;
    }
}
