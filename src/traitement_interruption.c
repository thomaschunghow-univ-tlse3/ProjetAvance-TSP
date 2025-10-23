

#include "traitement_interruption.h"
#include "affichage.h"

#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

volatile sig_atomic_t interruption = false; /* Drapeau pour indiquer la réception du signal. */

void gestionnaire_interruption(int signal)
{
    interruption = 1;
    (void)signal;
}

bool traitement_interruption(Permutation permutation, Permutation permutation_minimale, distance longueur_minimale)
{
    interruption = false; /* Réinitialisation du drapeau. */

    printf(ROUGE "\n");

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
        printf("Arrêt du calcul.\n\n");
        printf(RESET);

        return true;
    }

    printf("Reprise du calcul.\n\n");
    printf(RESET);

    return false;
}
