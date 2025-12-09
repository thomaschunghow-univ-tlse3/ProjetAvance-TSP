/*
 * traitement_interruption.c
 */

#include "traitement_interruption.h"

#include "affichage.h"
#include "options.h"
#include "structure_matrice.h"
#include "structure_permutation.h"
#include "structure_tableau_permutation.h"

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Permutation global_permutation_courante;
Permutation global_permutation_resultat;
clock_t global_temps_initial;
Arguments global_arguments;
MatriceDistance global_matrice;
TableauPermutation global_population;
TableauPermutation global_enfants;
TableauPermutation global_parents;
Permutation global_inverse;
TableauMorceau global_morceaux;

void interruption_proteger_signal(int signal, void (*traiter_signal)(int signal), struct sigaction *ancienne_action)
{
    struct sigaction action;

    action.sa_flags = 0;

    action.sa_handler = traiter_signal;

    if (sigemptyset(&action.sa_mask) == -1)
    {
        perror("Erreur sigemptyset ");
        exit(EXIT_FAILURE);
    };

    if (sigaction(signal, &action, ancienne_action) == -1)
    {
        perror("Erreur sigaction ");
        exit(EXIT_FAILURE);
    }
}

void interruption_retablir_masque(int signal, struct sigaction *action)
{
    if (sigaction(signal, action, NULL) == -1)
    {
        perror("Erreur sigaction ");
        exit(EXIT_FAILURE);
    }
}

void interruption_force_brute_traiter_signal(int signal)
{
    (void)signal;

    printf(ROUGE "\n");

    printf("Tournée courante                 : ");
    afficher_permutation(stdout, global_permutation_courante, 20);
    printf("\n");

    printf("Meilleure tournée trouvée        : ");
    afficher_permutation(stdout, global_permutation_resultat, 20);
    printf("\n");

    printf("Longueur de la meilleure tournée : ");
    afficher_longueur(stdout, global_permutation_resultat);
    printf("\n\n");

    int reponse = ' ';

    while (reponse != 'y' && reponse != 'Y' && reponse != 'n' && reponse != 'N')
    {
        printf("Continuer ? [Y/n] : ");

        reponse = getchar();

        int vidange;
        while ((vidange = getchar()) != '\n' && vidange != EOF)
            ;
    }

    if (reponse == 'y' || reponse == 'Y')
    {
        printf("Reprise du calcul.");
        printf(RESET "\n");

        return;
    }

    printf("Arrêt du calcul.");
    printf(RESET "\n");

    clock_t temps_total = clock() - global_temps_initial;
    double temps_en_secondes = (double)temps_total;
    temps_en_secondes /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, global_arguments.nom_fichier_entree, FORCE_BRUTE, temps_en_secondes,
                     global_permutation_resultat);

    permutation_supprimer(&global_permutation_courante);
    permutation_supprimer(&global_permutation_resultat);

    matrice_supprimer(&global_matrice);

    fichier_fermer_entree(global_arguments);
    fichier_fermer_sortie(global_arguments);

    exit(EXIT_SUCCESS);
}

void interruption_2_optimisation_plus_proche_voisin_traiter_signal(int signal)
{
    (void)signal;

    printf(ROUGE "\n");

    printf("Tournée courante                 : ");
    afficher_permutation(stdout, global_permutation_courante, 20);
    printf("\n");

    printf("Longueur de la tournée           : ");
    afficher_longueur(stdout, global_permutation_resultat);
    printf("\n\n");

    int reponse = ' ';

    while (reponse != 'y' && reponse != 'Y' && reponse != 'n' && reponse != 'N')
    {
        printf("Continuer ? [Y/n] : ");

        reponse = getchar();

        int vidange;
        while ((vidange = getchar()) != '\n' && vidange != EOF)
            ;
    }

    if (reponse == 'y' || reponse == 'Y')
    {
        printf("Reprise du calcul.");
        printf(RESET "\n");

        return;
    }

    printf("Arrêt du calcul.");
    printf(RESET "\n");

    clock_t temps_total = clock() - global_temps_initial;
    double temps_en_secondes = (double)temps_total;
    temps_en_secondes /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, global_arguments.nom_fichier_entree, PLUS_PROCHE_VOISIN_2_OPTIMISATION, temps_en_secondes,
                     global_permutation_resultat);

    permutation_supprimer(&global_permutation_courante);
    permutation_supprimer(&global_permutation_resultat);

    matrice_supprimer(&global_matrice);

    fichier_fermer_entree(global_arguments);
    fichier_fermer_sortie(global_arguments);

    exit(EXIT_SUCCESS);
}

void interruption_2_optimisation_marche_aleatoire_traiter_signal(int signal)
{
    (void)signal;

    printf(ROUGE "\n");

    printf("Tournée courante                 : ");
    afficher_permutation(stdout, global_permutation_courante, 20);
    printf("\n");

    printf("Longueur de la tournée           : ");
    afficher_longueur(stdout, global_permutation_resultat);
    printf("\n\n");

    int reponse = ' ';

    while (reponse != 'y' && reponse != 'Y' && reponse != 'n' && reponse != 'N')
    {
        printf("Continuer ? [Y/n] : ");

        reponse = getchar();

        int vidange;
        while ((vidange = getchar()) != '\n' && vidange != EOF)
            ;
    }

    if (reponse == 'y' || reponse == 'Y')
    {
        printf("Reprise du calcul.");
        printf(RESET "\n");

        return;
    }

    printf("Arrêt du calcul.");
    printf(RESET "\n");

    clock_t temps_total = clock() - global_temps_initial;
    double temps_en_secondes = (double)temps_total;
    temps_en_secondes /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, global_arguments.nom_fichier_entree, MARCHE_ALEATOIRE_2_OPTIMISATION, temps_en_secondes,
                     global_permutation_resultat);

    permutation_supprimer(&global_permutation_courante);
    permutation_supprimer(&global_permutation_resultat);

    matrice_supprimer(&global_matrice);

    fichier_fermer_entree(global_arguments);
    fichier_fermer_sortie(global_arguments);

    exit(EXIT_SUCCESS);
}

void interruption_genetique_light_traiter_signal(int signal)
{
    (void)signal;

    printf(ROUGE "\n");

    printf("Meilleure tournée historique     : ");
    afficher_permutation(stdout, global_permutation_resultat, 20);
    printf("\n");

    printf("Longueur de la tournée           : ");
    afficher_longueur(stdout, global_permutation_resultat);
    printf("\n\n");

    int reponse = ' ';

    while (reponse != 'y' && reponse != 'Y' && reponse != 'n' && reponse != 'N')
    {
        printf("Continuer ? [Y/n] : ");

        reponse = getchar();

        int vidange;
        while ((vidange = getchar()) != '\n' && vidange != EOF)
            ;
    }

    if (reponse == 'y' || reponse == 'Y')
    {
        printf("Reprise du calcul.");
        printf(RESET "\n");

        return;
    }

    printf("Arrêt du calcul.");
    printf(RESET "\n");

    clock_t temps_total = clock() - global_temps_initial;
    double temps_en_secondes = (double)temps_total;
    temps_en_secondes /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, global_arguments.nom_fichier_entree, GENETIQUE_LIGHT, temps_en_secondes,
                     global_permutation_resultat);

    permutation_supprimer(&global_permutation_resultat);

    matrice_supprimer(&global_matrice);

    tableau_permutation_supprimer(&global_population);
    tableau_permutation_supprimer(&global_enfants);
    tableau_permutation_supprimer(&global_parents);
    permutation_supprimer(&global_inverse);

    fichier_fermer_entree(global_arguments);
    fichier_fermer_sortie(global_arguments);

    exit(EXIT_SUCCESS);
}

void interruption_genetique_dpx_traiter_signal(int signal)
{
    (void)signal;

    printf(ROUGE "\n");

    printf("Meilleure tournée historique     : ");
    afficher_permutation(stdout, global_permutation_resultat, 20);
    printf("\n");

    printf("Longueur de la tournée           : ");
    afficher_longueur(stdout, global_permutation_resultat);
    printf("\n\n");

    int reponse = ' ';

    while (reponse != 'y' && reponse != 'Y' && reponse != 'n' && reponse != 'N')
    {
        printf("Continuer ? [Y/n] : ");

        reponse = getchar();

        int vidange;
        while ((vidange = getchar()) != '\n' && vidange != EOF)
            ;
    }

    if (reponse == 'y' || reponse == 'Y')
    {
        printf("Reprise du calcul.");
        printf(RESET "\n");

        return;
    }

    printf("Arrêt du calcul.");
    printf(RESET "\n");

    clock_t temps_total = clock() - global_temps_initial;
    double temps_en_secondes = (double)temps_total;
    temps_en_secondes /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, global_arguments.nom_fichier_entree, GENETIQUE_DPX, temps_en_secondes,
                     global_permutation_resultat);

    permutation_supprimer(&global_permutation_resultat);

    matrice_supprimer(&global_matrice);

    tableau_permutation_supprimer(&global_population);
    tableau_permutation_supprimer(&global_enfants);
    tableau_permutation_supprimer(&global_parents);
    permutation_supprimer(&global_inverse);
    tableau_morceau_supprimer(&global_morceaux);

    fichier_fermer_entree(global_arguments);
    fichier_fermer_sortie(global_arguments);

    exit(EXIT_SUCCESS);
}
