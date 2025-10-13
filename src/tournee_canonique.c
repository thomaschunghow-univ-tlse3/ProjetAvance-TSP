/*
 */

#include "tournee_canonique.h"
#include "affichage.h"

Resultat calcul_tournee_canonique(MatriceDistances matrice)
{
    size_t nombre_points = nombre_points_matrice(matrice);
    size_t nombre_distances = nombre_points - 1;

    Resultat resultat;
    resultat.permutation = creer_permutation(nombre_points);
    resultat.distance = 0;

    for (size_t i = 0; i < nombre_distances; i++)
    {
        resultat.distance += *obtenir_distance_matrice(matrice, i, i + 1);
    }

    return resultat;
}
