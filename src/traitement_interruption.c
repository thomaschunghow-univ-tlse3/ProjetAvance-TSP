/*
 * traitement_interruption.c
 */

#include "traitement_interruption.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

volatile sig_atomic_t interruption = false; /* Drapeau pour indiquer la réception du signal. */

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

void interruption_receptionner_signal(int signal)
{
    interruption = true;
    (void)signal;
}

bool interruption_traiter_signal(Permutation permutation, Permutation permutation_minimale)
{
    interruption = false; /* Réinitialisation du drapeau. */

    printf(ROUGE "\n");

    printf("Tournée courante                 : ");
    afficher_permutation(stdout, permutation, 20);
    printf("\n");

    printf("Meilleure tournée trouvée        : ");
    afficher_permutation(stdout, permutation_minimale, 20);
    printf("\n");

    printf("Longueur de la meilleure tournée : ");
    afficher_longueur(stdout, permutation_minimale);
    printf("\n\n");

    int reponse = ' ';
    int vidange;

    while (reponse != 'y' && reponse != 'Y' && reponse != 'n' && reponse != 'N')
    {
        printf("Continuer ? [Y/n] : ");

        reponse = getchar();

        while ((vidange = getchar()) != '\n' && vidange != EOF)
            ;
    }

    if (reponse == 'n' || reponse == 'N')
    {
        printf("Arrêt du calcul.");
        printf(RESET "\n");

        return true;
    }

    printf("Reprise du calcul.");
    printf(RESET "\n");

    return false;
}
