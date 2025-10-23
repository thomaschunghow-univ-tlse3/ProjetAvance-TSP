/*
 * affichage.c
 */

#include "affichage.h"

#include <unistd.h>
#include <stdlib.h>

void afficher_noms_champs(FILE *sortie)
{
    fprintf(sortie, "Instance ; Méthode ; Temps CPU (secondes) ; Longueur ; Tour ;\n");
}

void afficher_permutation(FILE *sortie, Permutation permutation)
{
    size_t nombre_points = permutation_obtenir_taille(permutation);

    fprintf(sortie, "[");
    for (size_t i = 0; i < nombre_points - 1; i++)
    {
        fprintf(sortie, "%ld,", permutation_obtenir_indice(permutation, i) + 1);
    }
    fprintf(sortie, "%ld", permutation_obtenir_indice(permutation, nombre_points - 1) + 1);
    fprintf(sortie, "]");
}

void afficher_methode_calcul(FILE *sortie, MethodeCalcul methode)
{
    switch (methode)
    {
    case CANONIQUE:
        fprintf(sortie, "canonique");
        break;
    case BF:
        fprintf(sortie, "bf");
        break;
    case NN:
        fprintf(sortie, "nn");
        break;
    case RW:
        fprintf(sortie, "rw");
        break;
    case NN2OPT:
        fprintf(sortie, "2optnn");
        break;
    case RW2OPT:
        fprintf(sortie, "2optrw");
        break;
    case GA:
        fprintf(sortie, "ga");
        break;
    case GADPX:
        fprintf(sortie, "gadpx");
        break;
    default:
        fprintf(stderr,
                "Erreur afficher_methode_calcul :\n"
                "La méthode choisie n'est pas une méthode affichable.\n");
        exit(EXIT_FAILURE);
    }
}

void afficher_longueur(FILE *sortie, distance distance)
{
    fprintf(sortie, "%.17g", distance);
}

void afficher_tournee(FILE *sortie, char *nom_fichier, MethodeCalcul methode, double temps, distance distance_totale, Permutation permutation)
{
    fprintf(sortie, "%s ; ", nom_fichier);

    afficher_methode_calcul(sortie, methode);
    fprintf(sortie, " ; ");

    fprintf(sortie, "%lf ; ", temps);

    afficher_longueur(sortie, distance_totale);
    fprintf(sortie, " ; ");

    afficher_permutation(sortie, permutation);
    fprintf(sortie, " ; ");

    fprintf(sortie, "\n");
}
