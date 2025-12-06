/*
 * traitement_interruption.c
 */

#include "traitement_interruption.h"

#include "affichage.h"
#include "options.h"
#include "structure_permutation.h"

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Permutation permutation_courante;
Permutation permutation_minimale;
clock_t temps_initial;
Arguments arguments;
MatriceDistance matrice;

void interruption_proteger_signal(int signal, void (*traiter_signal)(int signal))
{
    struct sigaction action;

    action.sa_flags = 0;

    action.sa_handler = traiter_signal;

    if (sigemptyset(&action.sa_mask) == -1)
    {
        perror("Erreur sigemptyset ");
        exit(EXIT_FAILURE);
    };

    if (sigaction(signal, &action, NULL) == -1)
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
    afficher_permutation(stdout, permutation_courante, 20);
    printf("\n");

    printf("Meilleure tournée trouvée        : ");
    afficher_permutation(stdout, permutation_minimale, 20);
    printf("\n");

    printf("Longueur de la meilleure tournée : ");
    afficher_longueur(stdout, permutation_minimale);
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

    clock_t temps_total = clock() - temps_initial;
    double temps_en_secondes = (double)temps_total;
    temps_en_secondes /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, arguments.nom_fichier_entree, FORCE_BRUTE, temps_en_secondes, permutation_minimale);

    permutation_supprimer(&permutation_courante);
    permutation_supprimer(&permutation_minimale);

    matrice_supprimer(&matrice);

    fichier_fermer_entree(arguments);
    fichier_fermer_sortie(arguments);

    exit(EXIT_SUCCESS);
}
