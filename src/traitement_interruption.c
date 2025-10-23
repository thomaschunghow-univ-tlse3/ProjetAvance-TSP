

#include "traitement_interruption.h"
#include "affichage.h"

#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

volatile sig_atomic_t flag = 0; // variable globale pour indiquer la réception du signal

void changement_etat(int signal)
{
    (void)signal; // Ignorer le paramètre inutilisé
    flag = 1;
}

void gerer_interruption_bf(distance d_courante, distance d_minimale, Permutation meilleure_permutation, Permutation permutation_courante, bool *stop)
{

    flag = 0; // Réinitialiser le drapeau

    printf("\n INTERRUPTION \n");
    printf("Meilleure distance trouvée: %.2f\n", d_minimale);
    printf("Meilleur tournée trouvée: ");
    afficher_permutation(stdout, meilleure_permutation);
    printf("\n");
    printf("Permutation actuelle    : %.2f\n", d_courante);
    printf("Tournée actuelle : ");
    afficher_permutation(stdout, permutation_courante);
    printf("\n");
    fflush(stdout);

    char reponse = ' ';
    int c;

    while (reponse != 'c' && reponse != 'C' && reponse != 's' && reponse != 'S')
    {
        printf("\nVeuillez entrer 'c' pour CONTINUER ou 's' pour STOPPER : ");
        reponse = getchar(); // Lire le caractère de l'utilisateur
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Vider le buffer d'entrée
    }

    if (reponse == 's' || reponse == 'S')
    {
        printf("Arrêt du calcul demandé\n");
        *stop = true; // correction de la valeur pointé
    }
    else if (reponse == 'c' || reponse == 'C')
    {
        printf("Reprise du calcul\n");
        signal(SIGINT, changement_etat);
    }
    fflush(stdout);
}
