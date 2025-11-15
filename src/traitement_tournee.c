/*
 * traitement_tournee.c
 */

#include "traitement_tournee.h"
#include "affichage.h"
#include "tournee_canonique.h"
#include "traitement_interruption.h"
#include "tournee_force_brute.h"
#include "tournee_2_optimisation.h"
#include "tournee_genetique.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>

void tournee_gestionnaire(FILE *sortie, Options options, MatriceDistance matrice, MethodeCalcul methode)
{
    clock_t temps = clock();

    signal(SIGINT, interruption_gestionnaire);
    Resultat resultat;
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

    case GENETIQUE_GENERIQUE:
        resultat = tournee_genetique_generique(matrice,
                                               options.arguments_genetique.nombre_individus,
                                               options.arguments_genetique.nombre_generations,
                                               options.arguments_genetique.taux_mutation);
        break;

    case GENETIQUE_DPX:
        resultat = tournee_genetique_dpx(matrice,
                                         options.arguments_genetique.nombre_individus,
                                         options.arguments_genetique.nombre_generations,
                                         options.arguments_genetique.taux_mutation);
        break;

    case TOUTES:
        exit(EXIT_FAILURE);
        break;
    }
    signal(SIGINT, SIG_DFL);

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

#ifndef AFFICHAGE_INTERACTIF
    afficher_tournee(sortie, options.nom_fichier_entree, methode, temps_total, resultat.longueur, resultat.permutation);
#else
    (void)sortie;
#endif // AFFICHAGE_INTERACTIF

    permutation_supprimer(&resultat.permutation);
}

void tournee_traitement(FILE *sortie, Options options, MatriceDistance matrice)
{
    srand((unsigned int)time(NULL)); /* Initialisation de la graine pour la génération de nombres aléatoires. */

#ifndef AFFICHAGE_INTERACTIF
    afficher_noms_champs(sortie);
#else  // AFFICHAGE_INTERACTIF
    afficher_points(sortie_interactive, matrice);
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
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE);

        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE);

        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        tournee_gestionnaire(sortie, options, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        break;

    case GENETIQUE_GENERIQUE:
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_GENERIQUE);
        break;

    case GENETIQUE_DPX:
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_DPX);
        break;

    case TOUTES:
        tournee_gestionnaire(sortie, options, matrice, PLUS_PROCHE_VOISIN);
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE);
        tournee_gestionnaire(sortie, options, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        tournee_gestionnaire(sortie, options, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_GENERIQUE);
        tournee_gestionnaire(sortie, options, matrice, GENETIQUE_DPX);
        break;

    default:
        break;
    }
}

/* Donne un entier aléatoire compris entre borne_inf et borne_sup exclus.
 * borne_inf <= entier_aleatoire < borne_sup */
size_t donner_entier_aleatoire(size_t borne_inf, size_t borne_sup)
{
    return borne_inf + rand() % (borne_sup - borne_inf);
}

/* Donne un réel aléatoire compris entre borne_inf et borne_sup exclus.
 * borne_inf <= reel_aleatoire < borne_sup */
size_t donner_reel_aleatoire(size_t borne_inf, size_t borne_sup)
{
    return borne_inf + rand() / RAND_MAX * (borne_sup - borne_inf);
}
