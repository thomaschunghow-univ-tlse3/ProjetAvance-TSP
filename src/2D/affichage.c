/*
 * affichage.c
 */

#include "affichage.h"

#include "calcul_distance.h"
#include "traitement_tournee.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void afficher_noms_champs(FILE *sortie)
{
    fprintf(sortie, "Instance ; "
                    "Méthode ; "
                    "Temps CPU (s) ; "
                    "Longueur ; "
                    "Tour "
                    "\n");
}

void afficher_points(FILE *sortie, MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);
    for (size_t i = 0; i < nombre_points; i++)
    {
        Point point;
        matrice_obtenir_point(matrice, i, &point);
        fprintf(sortie, "%lf,", point.x);
    }
    fprintf(sortie, "\n");
    for (size_t i = 0; i < nombre_points; i++)
    {
        Point point;
        matrice_obtenir_point(matrice, i, &point);
        fprintf(sortie, "%lf,", point.y);
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

void afficher_methode_calcul(FILE *sortie, Methode methode)
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
    case GENETIQUE_LIGHT:
        fprintf(sortie, "ga       ");
        break;
    case GENETIQUE_DPX:
        fprintf(sortie, "gadpx    ");
        break;
    default:
        fprintf(stderr, "Erreur afficher_methode_calcul :\n"
                        "La méthode choisie n'est pas une méthode affichable.\n");
        exit(EXIT_FAILURE);
    }
}

void afficher_longueur(FILE *sortie, Permutation permutation)
{
    assert(permutation != NULL);

    distance distance_a_afficher;
    permutation_obtenir_longueur(permutation, &distance_a_afficher);
    fprintf(sortie, "%-20.17g", distance_a_afficher);
}

void afficher_tournee(FILE *sortie, char *nom_fichier, Methode methode, double temps, Permutation permutation)
{
    fprintf(sortie, "%-25s ; ", nom_fichier);

    afficher_methode_calcul(sortie, methode);
    fprintf(sortie, " ; ");

    fprintf(sortie, "%-13.7f ; ", temps);

    afficher_longueur(sortie, permutation);
    fprintf(sortie, " ; ");

    afficher_permutation(sortie, permutation, 0);

    fprintf(sortie, "\n");
}

void afficher_morceaux(FILE *sortie, TableauMorceau morceaux)
{
    for (size_t i = 0; i < tableau_morceau_obtenir_nombre_morceaux(morceaux); i++)
    {
        fprintf(sortie, "Morceau %lu : Nombre sommets = %lu, Sommet gauche  = %lu, Sommet droit   = %lu\n", i,
                tableau_morceau_obtenir_nombre_sommets(morceaux, i), tableau_morceau_obtenir_sommet_gauche(morceaux, i),
                tableau_morceau_obtenir_sommet_droit(morceaux, i));
    }
}
