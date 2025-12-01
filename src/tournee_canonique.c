/*
 * tournee_canonique.c
 */

#include "tournee_canonique.h"

Permutation tournee_canonique(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Permutation permutation = permutation_creer(nombre_points, matrice_obtenir_taille_distance(matrice));
    permutation_calculer_longueur(permutation, matrice);

    return permutation;
}
