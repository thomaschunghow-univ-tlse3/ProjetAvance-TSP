/*
 */

#include "traitement_tournee.h"
#include "affichage.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"

#include <time.h>
#include <math.h>

void traitement_tournee(FILE *sortie, Options options, MatriceDistance matrice, AlgorithmeTournee calculer_tournee)
{
    clock_t temps = clock();

    Resultat resultat = calculer_tournee(matrice);

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, options.nom_fichier_entree, options.methode_calcul, temps_total, resultat.distance, resultat.permutation);

    permutation_supprimer(&resultat.permutation);
}

void calcul_tournee(FILE *sortie, Options options, MatriceDistance matrice)
{
    afficher_noms_champs(sortie);

    if (options.canonique)
    {
        traitement_tournee(sortie, options, matrice, &calcul_tournee_canonique);
    }
    switch (options.methode_calcul)
    {
    case BF:
        traitement_tournee(sortie, options, matrice, &calcul_tournee_force_brute);
        break;
    case NN:
        traitement_tournee(sortie, options, matrice, NULL);
        break;
    case RW:
        traitement_tournee(sortie, options, matrice, NULL);
        break;
    case NN2OPT:
        traitement_tournee(sortie, options, matrice, NULL);
        break;
    case RW2OPT:
        traitement_tournee(sortie, options, matrice, NULL);
        break;
    case GA:
        traitement_tournee(sortie, options, matrice, NULL);
        break;
    case GADPX:
        traitement_tournee(sortie, options, matrice, NULL);
        break;
    case ALL:
        traitement_tournee(sortie, options, matrice, NULL);
        traitement_tournee(sortie, options, matrice, NULL);
        traitement_tournee(sortie, options, matrice, NULL);
        traitement_tournee(sortie, options, matrice, NULL);
        traitement_tournee(sortie, options, matrice, NULL);
        traitement_tournee(sortie, options, matrice, NULL);
        break;
    default:
        break;
    }
}
