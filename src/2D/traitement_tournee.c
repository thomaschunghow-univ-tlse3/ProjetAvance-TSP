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

void tournee_gerer_algorithme(FILE *sortie, Arguments options, MatriceDistance matrice, Methode methode)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    size_t taille_distance = matrice_obtenir_taille_distance(matrice);

    temps_initial = clock();

    permutation_minimale = permutation_creer(nombre_points, taille_distance);

    switch (methode)
    {
    case CANONIQUE:
        permutation_minimale = tournee_canonique(matrice);
        break;

    case FORCE_BRUTE:

        permutation_courante = permutation_creer(nombre_points, taille_distance);

        interruption_proteger_signal(SIGINT, interruption_force_brute_traiter_signal);

        tournee_force_brute_incrementale(matrice, permutation_courante, permutation_minimale);

        permutation_supprimer(&permutation_courante);
        break;

    case PLUS_PROCHE_VOISIN:
        permutation_minimale = tournee_plus_proche_voisin(matrice);
        break;

    case MARCHE_ALEATOIRE:
        permutation_minimale = tournee_marche_aleatoire(matrice);
        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        permutation_minimale = tournee_2_optimisation_plus_proche_voisin(matrice);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        permutation_minimale = tournee_2_optimisation_marche_aleatoire(matrice);
        break;

    case GENETIQUE_LIGHT:
        permutation_minimale = tournee_genetique_light(
            matrice,
            options.arguments_genetique.nombre_individus,
            options.arguments_genetique.nombre_generations,
            options.arguments_genetique.taux_mutation,
            options.arguments_genetique.nombre_individus / 2);
        break;

    case GENETIQUE_DPX:
        permutation_minimale = tournee_genetique_dpx(
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

    clock_t temps_ecoule = clock() - temps_initial;
    double secondes_ecoulees = (double)temps_ecoule;
    secondes_ecoulees /= CLOCKS_PER_SEC;

#ifdef AFFICHAGE_INTERACTIF_2_OPT
    (void)sortie;
    (void)secondes_ecoulees;
    (void)options;
#else
#ifdef AFFICHAGE_INTERACTIF_GA
    (void)sortie;
    (void)secondes_ecoulees;
    (void)options;
#else
    afficher_tournee(sortie, options.nom_fichier_entree, methode, secondes_ecoulees, permutation_minimale);
#endif // AFFICHAGE_INTERACTIF_GA
#endif // AFFICHAGE_INTERACTIF_2_OPT

    permutation_supprimer(&permutation_minimale);
}

void tournee_traiter_methode(FILE *sortie, Arguments options, MatriceDistance matrice)
{
    srand((unsigned int)time(NULL)); /* Initialisation de la graine pour la génération de nombres aléatoires. */

#ifdef AFFICHAGE_INTERACTIF_2_OPT
    afficher_points(sortie, matrice);
#else
#ifdef AFFICHAGE_INTERACTIF_GA
    afficher_points(sortie, matrice);
#else
    afficher_noms_champs(sortie);
#endif // AFFICHAGE_INTERACTIF_GA
#endif // AFFICHAGE_INTERACTIF_2_OPT

    if (options.canonique)
    {
        tournee_gerer_algorithme(sortie, options, matrice, CANONIQUE);
    }

    switch (options.methode_calcul)
    {
    case FORCE_BRUTE:
        tournee_gerer_algorithme(sortie, options, matrice, FORCE_BRUTE);
        break;

    case PLUS_PROCHE_VOISIN:
        tournee_gerer_algorithme(sortie, options, matrice, PLUS_PROCHE_VOISIN);
        break;

    case MARCHE_ALEATOIRE:
        tournee_gerer_algorithme(sortie, options, matrice, MARCHE_ALEATOIRE);
        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        tournee_gerer_algorithme(sortie, options, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        tournee_gerer_algorithme(sortie, options, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        break;

    case GENETIQUE_LIGHT:
        tournee_gerer_algorithme(sortie, options, matrice, GENETIQUE_LIGHT);
        break;

    case GENETIQUE_DPX:
        tournee_gerer_algorithme(sortie, options, matrice, GENETIQUE_DPX);
        break;

    case TOUTES:
        tournee_gerer_algorithme(sortie, options, matrice, PLUS_PROCHE_VOISIN);
        tournee_gerer_algorithme(sortie, options, matrice, MARCHE_ALEATOIRE);
        tournee_gerer_algorithme(sortie, options, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        tournee_gerer_algorithme(sortie, options, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        tournee_gerer_algorithme(sortie, options, matrice, GENETIQUE_LIGHT);
        tournee_gerer_algorithme(sortie, options, matrice, GENETIQUE_DPX);
        break;

    default:
        break;
    }
}
