/*
 */

#include "tournee_force_brute.h"
#include "structure_permutation.h"
#include "tournee_canonique.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stddef.h>
#include <signal.h>

static volatile sig_atomic_t flag = 0; // variable globale pour indiquer la réception du signal

/*Permet de lever le drapeau d'interruption*/
static void changement_etat(int sig)
{
    (void)sig; // éviter l'avertissement de variable non utilisée
    flag = 1;  // définir le drapeau lorsque le signal est reçu
}

Resultat brute_force(MatriceDistance matrice)
{
    signal(SIGINT, changement_etat);

    size_t nombre_points = matrice_nombre_points(matrice);
    Permutation permutation_courante = creer_permutation(nombre_points);
    Permutation meilleure_permutation = creer_permutation(nombre_points);

    distance d_courante;
    distance d_minimale;
    distance d_maximal = 0.0; // Initialisation

    bool stop = false;
    bool premiere_permutation = true;

    do
    { // Utilisation d'un do-while pour inclure la première permutation
        d_courante = distance_totale_permutation(permutation_courante, matrice);

        if (premiere_permutation)
        {
            d_minimale = d_courante;
            d_maximal = d_courante;
            copier_tableau(meilleure_permutation, permutation_courante);
            premiere_permutation = false;
        }

        if (flag)
        {

            flag = 0; // Réinitialiser le drapeau

            printf("\n INTERRUPTION \n");
            printf("Pire distance trouvée   : %.2f\n", d_maximal);
            printf("Meilleure distance trouvée: %.2f\n", d_minimale);
            printf("Permutation actuelle    : %.2f\n", d_courante);
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
                stop = true;
            }
            else if (reponse == 'c' || reponse == 'C')
            {
                printf("Reprise du calcul\n");
                flag = 0;
                signal(SIGINT, changement_etat);
            }
        }

        if (d_courante < d_minimale)
        {
            d_minimale = d_courante;
            copier_tableau(meilleure_permutation, permutation_courante);
        }

        if (d_courante > d_maximal)
        {
            d_maximal = d_courante;
        }

    } while (permutation_suivante(permutation_courante) && !stop);

    supprimer_permutation(&permutation_courante);
    signal(SIGINT, SIG_DFL);

    Resultat resultat_final;
    resultat_final.permutation = meilleure_permutation;
    resultat_final.distance = d_minimale;

    return resultat_final;
}

Resultat calcul_tournee_force_brute(MatriceDistance matrice)
{
    return brute_force(matrice);
}
