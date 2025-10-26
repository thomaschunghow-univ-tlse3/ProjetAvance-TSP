/*
 * traitement_tournee.c
 */

#include "traitement_tournee.h"
#include "affichage.h"
#include "tournee_canonique.h"
#include "traitement_interruption.h"
#include "tournee_force_brute.h"
#include "tournee_2_optimisation.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>

void tournee_gestionnaire(FILE *sortie, char *nom_fichier_entree, MatriceDistance matrice, MethodeCalcul methode, AlgorithmeTournee calculer_tournee)
{
    clock_t temps = clock();

    srand((unsigned int)time(NULL)); /* Initialisation de la graine pour la génération de nombres aléatoires. */

    signal(SIGINT, interruption_gestionnaire);
    Resultat resultat = calculer_tournee(matrice);
    signal(SIGINT, SIG_DFL);

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, nom_fichier_entree, methode, temps_total, resultat.longueur, resultat.permutation);

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
    case FORCE_BRUTE:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, FORCE_BRUTE, &tournee_force_brute_incrementale);
        break;

    case PLUS_PROCHE_VOISIN:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, PLUS_PROCHE_VOISIN, &tournee_plus_proche_voisin);
        break;

    case MARCHE_ALEATOIRE:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, MARCHE_ALEATOIRE, &tournee_marche_aleatoire);
        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION, &tournee_2_optimisation_plus_proche_voisin);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION, &tournee_2_optimisation_marche_aleatoire);
        break;

    case GENETIQUE_GENERIQUE:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, GENETIQUE_GENERIQUE, &tournee_canonique);
        break;

    case GENETIQUE_DPX:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, GENETIQUE_DPX, &tournee_canonique);
        break;

    case TOUTES:
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, PLUS_PROCHE_VOISIN, &tournee_plus_proche_voisin);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, MARCHE_ALEATOIRE, &tournee_marche_aleatoire);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION, &tournee_2_optimisation_plus_proche_voisin);
        tournee_gestionnaire(sortie, options.nom_fichier_entree, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION, &tournee_2_optimisation_marche_aleatoire);
        break;

    default:
        break;
    }
}
