/*
 * traitement_interruption.c
 */

#include "traitement_interruption.h"
#include "affichage.h"
#include "calcul_distance.h"

#include <stdio.h>
#include <stdbool.h>

volatile sig_atomic_t interruption = false; /* Drapeau pour indiquer la réception du signal. */

void interruption_gestionnaire(int signal)
{
    interruption = true;
    (void)signal;
}

bool interruption_traitement(Permutation permutation, Permutation permutation_minimale)
{
    interruption = false; /* Réinitialisation du drapeau. */

    printf(ROUGE "\n");

    printf("Tournée courante                 : ");
    afficher_permutation(stdout, permutation, 10);
    printf("\n");

    printf("Meilleure tournée trouvée        : ");
    afficher_permutation(stdout, permutation_minimale, 10);
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
