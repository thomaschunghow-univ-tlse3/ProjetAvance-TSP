/*
 * traitement_interruption.c
 */

#include "traitement_interruption.h"
#include "affichage.h"

#include <stdio.h>
#include <stdbool.h>

volatile sig_atomic_t interruption = false; /* Drapeau pour indiquer la réception du signal. */

void gestionnaire_interruption(int signal)
{
    interruption = 1;
    (void)signal;
}

bool traitement_interruption(Permutation permutation, Permutation permutation_minimale, distance longueur_minimale, size_t nombre_permutations_traitees, size_t nombre_permutations_total)
{
    interruption = false; /* Réinitialisation du drapeau. */

    printf(ROUGE "\n");

    printf("%ld%% des tournées traitées.\n", 100 * nombre_permutations_traitees / nombre_permutations_total);

    printf("Tournée courante                 : ");
    afficher_permutation(stdout, permutation);
    printf("\n");

    printf("Meilleure tournée trouvée        : ");
    afficher_permutation(stdout, permutation_minimale);
    printf("\n");

    printf("Longueur de la meilleure tournée : ");
    afficher_longueur(stdout, longueur_minimale);
    printf("\n\n");

    char reponse = ' ';
    char vidange;

    while (reponse != 'y' && reponse != 'Y' && reponse != 'n' && reponse != 'N')
    {
        printf("Continuer ? [Y/n] : ");

        reponse = getchar();

        while ((vidange = getchar()) != '\n' && vidange != EOF)
        {
            ;
        }
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
