/*
 */

#include "affichage.h"

#include <unistd.h>
#include <stdlib.h>

void afficher_noms_champs(FILE *sortie)
{
    fprintf(sortie, "Instance ; Méthode ; Temps CPU (secondes) ; Longueur ; Tour\n");
}

// DEBUG : à supprimer éventuellement
void afficher_specification(FILE *sortie, Specification specification)
{
    fprintf(sortie,
            "%s\n"   // Nom
            "%s\n"   // Type
            "%s\n"   // Commentaire
            "%ld\n", // Nombre de points
            specification.nom,
            specification.type,
            specification.commentaire,
            specification.nombre_points);
}

// DEBUG : à supprimer éventuellement
void afficher_tableau_points(FILE *sortie, TableauPoints tableau)
{
    size_t nombre_points = taille_tableau_points(tableau);
    for (size_t i = 0; i < nombre_points; i++)
    {
        Point *point = obtenir_element_tableau_points(tableau, i);
        fprintf(sortie,
                "%ld "   // Indice du point
                "%lf "   // Coordonnée x
                "%lf\n", // Coordonnée y
                i + 1,
                point->x,
                point->y);
    }
}

// DEBUG : à supprimer éventuellement
void afficher_matrice(FILE *sortie, MatriceDistances matrice)
{
    size_t nombre_points = taille_tableau_points(tableau_points_matrice(matrice));
    for (size_t ligne = 0; ligne < nombre_points; ligne++)
    {
        for (size_t colonne = 0; colonne < ligne; colonne++)
        {
            distance *distance = obtenir_distance_matrice(matrice, ligne, colonne);
            fprintf(sortie,
                    "(%ld "  // Ligne
                    "%ld) "  // Colonne
                    "%lf\n", // Distance
                    ligne + 1,
                    colonne + 1,
                    *distance);
        }
    }
}

// DEBUG : à supprimer éventuellement
void afficher_tableau_distances(FILE *sortie, TableauDistances tableau)
{
    size_t nombre_distances = taille_tableau_distances(tableau);
    fprintf(sortie, "[");
    for (size_t i = 0; i < nombre_distances; i++)
    {
        distance distance = *obtenir_element_tableau_distances(tableau, i);
        fprintf(sortie,
                "%lf,\n",
                distance);
    }
    fprintf(sortie, "]\n");
}

// TODO : à décommenter après avoir implémenté le type permutation
// void afficher_permutation(FILE *sortie, Permutation permutation)
// {
//     size_t nombre_points = taille_permutation(permutation);
//     for (size_t i = 0; i < nombre_points - 1; i++)
//     {
//         fprintf(sortie, "%ld,", obtenir_element_permutation(permutation, i));
//     }
//     fprintf(sortie, "%ld] ;", obtenir_element_permutation(permutation, nombre_points - 1));
// }

void afficher_methode_calcul(FILE *sortie, MethodeCalcul methode)
{
    switch (methode)
    {
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
    case ALL:
        fprintf(stderr,
                "Erreur afficher_methode_calcul :\n"
                "'all' n'est pas une méthode affichable.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(sortie, " ; ");
}

void afficher_tournee(FILE *sortie, char *nom_fichier, MethodeCalcul methode, double temps, distance distance_totale, Resultat resultat)
{
    fprintf(sortie, "%s ; ", nom_fichier);

    afficher_methode_calcul(sortie, methode);

    fprintf(sortie, "%lf ; ", temps);

    fprintf(sortie, "%lf ; ", distance_totale);

    (void)resultat;
    // afficher_permutation(sortie, permutation);

    fprintf(sortie, "\n");
}
