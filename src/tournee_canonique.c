/*
 * tournee_canonique.c
 */

#include "tournee_canonique.h"
#include "affichage.h"

Resultat calcul_tournee_canonique(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Resultat resultat;
    resultat.permutation = permutation_creer(nombre_points);
    resultat.distance = permutation_calculer_distance_totale(resultat.permutation, matrice);

    return resultat;
}
