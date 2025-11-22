/*
 * affichage.c
 */

#include "affichage.h"

#include <unistd.h>
#include <stdlib.h>

void afficher_noms_champs(FILE *sortie)
{
    fprintf(
        sortie,
        "Instance ; "
        "Méthode ; "
        "Temps CPU (s) ; "
        "Longueur ; "
        "Tour ; "
        "\n");
}

void afficher_points(FILE *sortie, MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    for (size_t i = 0; i < nombre_points; i++)
    {
        fprintf(sortie, "%lf,", matrice_obtenir_point(matrice, i).x);
    }
    fprintf(sortie, "\n");
    for (size_t i = 0; i < nombre_points; i++)
    {
        fprintf(sortie, "%lf,", matrice_obtenir_point(matrice, i).y);
    }
    fprintf(sortie, "\n");
}

/* Convention : si le nombre points max est égal à 0, alors on utilise le vrai nombre de points. */
void afficher_permutation(FILE *sortie, Permutation permutation, size_t nombre_points_max)
{
    size_t nombre_points = permutation_obtenir_nombre_sommets(permutation);

    if (nombre_points_max == 0 || nombre_points_max >= nombre_points)
    {
        nombre_points_max = nombre_points;
    }

    fprintf(sortie, "[");
    for (size_t i = 0; i < nombre_points_max - 1; i++)
    {
        fprintf(sortie, "%ld,", permutation_obtenir_sommet(permutation, i) + 1);
    }

    if (nombre_points_max != nombre_points)
    {
        printf("...,");
    }

    fprintf(sortie, "%ld", permutation_obtenir_sommet(permutation, nombre_points - 1) + 1);
    fprintf(sortie, "]");
}

void afficher_methode_calcul(FILE *sortie, MethodeCalcul methode)
{
    switch (methode)
    {
    case CANONIQUE:
        fprintf(sortie, "canonique");
        break;
    case FORCE_BRUTE:
        fprintf(sortie, "bf       ");
        break;
    case PLUS_PROCHE_VOISIN:
        fprintf(sortie, "nn       ");
        break;
    case MARCHE_ALEATOIRE:
        fprintf(sortie, "rw       ");
        break;
    case PLUS_PROCHE_VOISIN_2_OPTIMISATION:
        fprintf(sortie, "2optnn   ");
        break;
    case MARCHE_ALEATOIRE_2_OPTIMISATION:
        fprintf(sortie, "2optrw   ");
        break;
    case GENETIQUE_GENERIQUE:
        fprintf(sortie, "ga       ");
        break;
    case GENETIQUE_DPX:
        fprintf(sortie, "gadpx    ");
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
    fprintf(sortie, "%-20.17g", distance);
}

void afficher_tournee(FILE *sortie, char *nom_fichier, MethodeCalcul methode, double temps, distance distance_totale, Permutation permutation)
{
    fprintf(sortie, "%s ; ", nom_fichier);

    afficher_methode_calcul(sortie, methode);
    fprintf(sortie, " ; ");

    fprintf(sortie, "%-13.7f ; ", temps);

    afficher_longueur(sortie, distance_totale);
    fprintf(sortie, " ; ");

    afficher_permutation(sortie, permutation, 0);

    fprintf(sortie, " ; ");

    fprintf(sortie, "\n");
}
