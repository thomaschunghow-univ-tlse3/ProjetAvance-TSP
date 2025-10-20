/*
 */

#include "affichage.h"

#include <unistd.h>
#include <stdlib.h>

void afficher_noms_champs(FILE *sortie)
{
    fprintf(sortie, "Instance ; Méthode ; Temps CPU (secondes) ; Longueur ; Tour ;\n");
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
    fprintf(sortie, " ; ");
}

void afficher_permutation(FILE *sortie, Permutation permutation)
{
    size_t nombre_points = nombre_indices(permutation);
    fprintf(sortie, "[");
    for (size_t i = 0; i < nombre_points - 1; i++)
    {
        fprintf(sortie, "%ld,", tableau_indices(permutation)[i] + 1);
    }
    fprintf(sortie, "%ld] ;", tableau_indices(permutation)[nombre_points - 1] + 1);
}

void afficher_tournee(FILE *sortie, char *nom_fichier, MethodeCalcul methode, double temps, distance distance_totale, Permutation permutation)
{
    fprintf(sortie, "%s ; ", nom_fichier);

    afficher_methode_calcul(sortie, methode);

    fprintf(sortie, "%lf ; ", temps);

    fprintf(sortie, "%.17g ; ", distance_totale);

    afficher_permutation(sortie, permutation);

    fprintf(sortie, "\n");
}
