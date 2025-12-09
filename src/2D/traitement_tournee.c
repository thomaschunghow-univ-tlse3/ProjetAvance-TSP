/*
 * traitement_tournee.c
 */

#include "traitement_tournee.h"

#include "affichage.h"
#include "options.h"
#include "structure_matrice.h"
#include "structure_morceau.h"
#include "structure_permutation.h"
#include "structure_tableau_permutation.h"
#include "tournee_2_optimisation.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"
#include "tournee_genetique.h"
#include "traitement_interruption.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

void tournee_conclure(FILE *sortie, Arguments arguments, Methode methode, Permutation permutation_resultat,
                      clock_t temps_initial)
{
    clock_t temps_ecoule = clock() - temps_initial;
    double secondes_ecoulees = (double)temps_ecoule;
    secondes_ecoulees /= CLOCKS_PER_SEC;

#ifdef AFFICHAGE_INTERACTIF_2_OPT
    (void)sortie;
    (void)arguments;
    (void)methode;
    (void)secondes_ecoulees;
#else // AFFICHAGE_INTERACTIF_2_OPT
#ifdef AFFICHAGE_INTERACTIF_GA
    (void)sortie;
    (void)arguments;
    (void)methode;
    (void)secondes_ecoulees;
#else  // AFFICHAGE_INTERACTIF_GA
    afficher_tournee(sortie, arguments.nom_fichier_entree, methode, secondes_ecoulees, permutation_resultat);
#endif // AFFICHAGE_INTERACTIF_GA
#endif // AFFICHAGE_INTERACTIF_2_OPT

    permutation_supprimer(&permutation_resultat);
}

void tournee_gerer_algorithme(FILE *sortie, Arguments arguments, MatriceDistance matrice, Methode methode)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    size_t taille_distance = matrice_obtenir_taille_distance(matrice);

    global_temps_initial = clock();

    global_permutation_resultat = permutation_creer(nombre_points, taille_distance);

    struct sigaction ancienne_action;

    switch (methode)
    {
    case CANONIQUE:
        global_permutation_resultat = tournee_canonique(matrice);
        break;

    case FORCE_BRUTE:
        global_permutation_courante = permutation_creer(nombre_points, taille_distance);

        interruption_proteger_signal(SIGINT, &interruption_force_brute_traiter_signal, &ancienne_action);

        tournee_force_brute_incrementale(matrice, global_permutation_courante, global_permutation_resultat);

        interruption_retablir_masque(SIGINT, &ancienne_action);

        permutation_supprimer(&global_permutation_courante);
        break;

    case PLUS_PROCHE_VOISIN:
        tournee_plus_proche_voisin(matrice, global_permutation_resultat);
        break;

    case MARCHE_ALEATOIRE:
        tournee_marche_aleatoire(matrice, global_permutation_resultat);
        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        global_permutation_courante = permutation_creer(nombre_points, taille_distance);

        interruption_proteger_signal(SIGINT, &interruption_2_optimisation_plus_proche_voisin_traiter_signal,
                                     &ancienne_action);

        tournee_2_optimisation_plus_proche_voisin(matrice, global_permutation_courante, global_permutation_resultat);

        interruption_retablir_masque(SIGINT, &ancienne_action);

        permutation_supprimer(&global_permutation_courante);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        global_permutation_courante = permutation_creer(nombre_points, taille_distance);

        interruption_proteger_signal(SIGINT, &interruption_2_optimisation_marche_aleatoire_traiter_signal,
                                     &ancienne_action);

        tournee_2_optimisation_marche_aleatoire(matrice, global_permutation_courante, global_permutation_resultat);

        interruption_retablir_masque(SIGINT, &ancienne_action);

        permutation_supprimer(&global_permutation_courante);
        break;

    case GENETIQUE_LIGHT:
        global_population =
            tableau_permutation_creer(arguments.arguments_genetique.nombre_individus,
                                      matrice_obtenir_nombre_points(matrice), matrice_obtenir_taille_distance(matrice));
        global_enfants =
            tableau_permutation_creer(arguments.arguments_genetique.nombre_individus,
                                      matrice_obtenir_nombre_points(matrice), matrice_obtenir_taille_distance(matrice));
        global_parents =
            tableau_permutation_creer(arguments.arguments_genetique.nombre_individus,
                                      matrice_obtenir_nombre_points(matrice), matrice_obtenir_taille_distance(matrice));
        global_inverse = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));

        interruption_proteger_signal(SIGINT, &interruption_genetique_light_traiter_signal, &ancienne_action);

        tournee_genetique_light(
            matrice, arguments.arguments_genetique.nombre_individus, arguments.arguments_genetique.nombre_generations,
            arguments.arguments_genetique.taux_mutation, arguments.arguments_genetique.nombre_individus / 2,
            global_permutation_resultat, global_population, global_enfants, global_parents, global_inverse);

        interruption_retablir_masque(SIGINT, &ancienne_action);

        tableau_permutation_supprimer(&global_population);
        tableau_permutation_supprimer(&global_enfants);
        tableau_permutation_supprimer(&global_parents);
        permutation_supprimer(&global_inverse);
        break;

    case GENETIQUE_DPX:
        global_population =
            tableau_permutation_creer(arguments.arguments_genetique.nombre_individus,
                                      matrice_obtenir_nombre_points(matrice), matrice_obtenir_taille_distance(matrice));
        global_enfants =
            tableau_permutation_creer(arguments.arguments_genetique.nombre_individus,
                                      matrice_obtenir_nombre_points(matrice), matrice_obtenir_taille_distance(matrice));
        global_parents =
            tableau_permutation_creer(arguments.arguments_genetique.nombre_individus,
                                      matrice_obtenir_nombre_points(matrice), matrice_obtenir_taille_distance(matrice));
        global_inverse = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));
        global_morceaux = tableau_morceau_creer(nombre_points);

        interruption_proteger_signal(SIGINT, &interruption_genetique_dpx_traiter_signal, &ancienne_action);

        tournee_genetique_dpx(matrice, arguments.arguments_genetique.nombre_individus,
                              arguments.arguments_genetique.nombre_generations,
                              arguments.arguments_genetique.taux_mutation,
                              arguments.arguments_genetique.nombre_individus / 2, global_permutation_resultat,
                              global_population, global_enfants, global_parents, global_inverse, global_morceaux);

        interruption_retablir_masque(SIGINT, &ancienne_action);

        tableau_permutation_supprimer(&global_population);
        tableau_permutation_supprimer(&global_enfants);
        tableau_permutation_supprimer(&global_parents);
        permutation_supprimer(&global_inverse);
        tableau_morceau_supprimer(&global_morceaux);
        break;

    case TOUTES:
        exit(EXIT_FAILURE);
        break;
    }

    tournee_conclure(sortie, arguments, methode, global_permutation_resultat, global_temps_initial);
}

void tournee_traiter_methode(FILE *sortie, Arguments arguments, MatriceDistance matrice)
{
#ifdef AFFICHAGE_INTERACTIF_2_OPT
    afficher_points(sortie, matrice);
#else
#ifdef AFFICHAGE_INTERACTIF_GA
    afficher_points(sortie, matrice);
#else
    afficher_noms_champs(sortie);
#endif // AFFICHAGE_INTERACTIF_GA
#endif // AFFICHAGE_INTERACTIF_2_OPT

    if (arguments.canonique)
    {
        tournee_gerer_algorithme(sortie, arguments, matrice, CANONIQUE);
    }

    switch (arguments.methode_calcul)
    {
    case FORCE_BRUTE:
        tournee_gerer_algorithme(sortie, arguments, matrice, FORCE_BRUTE);
        break;

    case PLUS_PROCHE_VOISIN:
        tournee_gerer_algorithme(sortie, arguments, matrice, PLUS_PROCHE_VOISIN);
        break;

    case MARCHE_ALEATOIRE:
        tournee_gerer_algorithme(sortie, arguments, matrice, MARCHE_ALEATOIRE);
        break;

    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        tournee_gerer_algorithme(sortie, arguments, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        break;

    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        tournee_gerer_algorithme(sortie, arguments, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        break;

    case GENETIQUE_LIGHT:
        tournee_gerer_algorithme(sortie, arguments, matrice, GENETIQUE_LIGHT);
        break;

    case GENETIQUE_DPX:
        tournee_gerer_algorithme(sortie, arguments, matrice, GENETIQUE_DPX);
        break;

    case TOUTES:
        tournee_gerer_algorithme(sortie, arguments, matrice, PLUS_PROCHE_VOISIN);
        tournee_gerer_algorithme(sortie, arguments, matrice, MARCHE_ALEATOIRE);
        tournee_gerer_algorithme(sortie, arguments, matrice, PLUS_PROCHE_VOISIN_2_OPTIMISATION);
        tournee_gerer_algorithme(sortie, arguments, matrice, MARCHE_ALEATOIRE_2_OPTIMISATION);
        tournee_gerer_algorithme(sortie, arguments, matrice, GENETIQUE_LIGHT);
        tournee_gerer_algorithme(sortie, arguments, matrice, GENETIQUE_DPX);
        break;

    default:
        break;
    }
}
