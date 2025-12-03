/*
 * traitement_tournee.c
 */

#include "traitement_tournee.h"

#include "affichage.h"
#include "options.h"
#include "structure_matrice.h"
#include "structure_permutation.h"
#include "tournee_2_optimisation.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"
#include "tournee_genetique.h"
#include "traitement_interruption.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

void tournee_gestionnaire(FILE *sortie, Arguments options, MatriceDistance matrice, Methode methode)
{
    clock_t temps = clock();

    interruption_proteger_signal(SIGINT, interruption_receptionner_signal);

    Permutation resultat;
    switch (methode)
    {
    case CANONIQUE:
        resultat = tournee_canonique(matrice);
        break;

    case FORCE_BRUTE:
        resultat = tournee_force_brute_incrementale(matrice);
        break;

    case PLUS_PROCHE_VOISIN:
        resultat = tournee_plus_proche_voisin(matrice);
        break;

    case MARCHE_ALEATOIRE:
        resultat = tournee_marche_aleatoire(matrice);
        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        resultat = tournee_2_optimisation_plus_proche_voisin(matrice);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        resultat = tournee_2_optimisation_marche_aleatoire(matrice);
        break;

    case GENETIQUE_LIGHT:
        resultat = tournee_genetique_light(
            matrice,
            options.arguments_genetique.nombre_individus,
            options.arguments_genetique.nombre_generations,
            options.arguments_genetique.taux_mutation,
            options.arguments_genetique.nombre_individus / 2);
        break;

    case GENETIQUE_DPX:
        resultat = tournee_genetique_dpx(
            matrice,
            options.arguments_genetique.nombre_individus,
            options.arguments_genetique.nombre_generations,
            options.arguments_genetique.taux_mutation,
            options.arguments_genetique.nombre_individus / 2);
        break;

    case TOUTES:
        exit(EXIT_FAILURE);
        break;
    }

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

#ifndef AFFICHAGE_INTERACTIF
    afficher_tournee(sortie, options.nom_fichier_entree, methode, temps_total, resultat);
#else
    (void)sortie;
    (void)temps_total;
    (void)options;
#endif // AFFICHAGE_INTERACTIF

    permutation_supprimer(&resultat);
}

void tournee_traitement(FILE *sortie, Arguments options, MatriceDistance matrice)
{
    srand((unsigned int)time(NULL)); /* Initialisation de la graine pour la génération de nombres aléatoires. */

#ifndef AFFICHAGE_INTERACTIF
    afficher_noms_champs(sortie);
#else  // AFFICHAGE_INTERACTIF
    afficher_points(sortie, matrice);
#endif // AFFICHAGE_INTERACTIF

    if (options.canonique)
    {
        tournee_gestionnaire(sortie, options, matrice, CANONIQUE);
    }

    switch (options.methode_calcul)
    {
    case FORCE_BRUTE:
        tournee_gestionnaire(sortie, options, matrice, FORCE_BRUTE);
        break;

    case PLUS_PROCHE_VOISIN:
        tournee_gestionnaire(sortie, options, matrice, PLUS_PROCHE_VOISIN);
        break;

    case MARCHE_ALEATOIRE:
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE);
        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        tournee_gestionnaire(sortie, options, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        break;

    case GENETIQUE_LIGHT:
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_LIGHT);
        break;

    case GENETIQUE_DPX:
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_DPX);
        break;

    case TOUTES:
        tournee_gestionnaire(sortie, options, matrice, PLUS_PROCHE_VOISIN);
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE);
        tournee_gestionnaire(sortie, options, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_LIGHT);
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_DPX);
        break;

    default:
        break;
    }
}
