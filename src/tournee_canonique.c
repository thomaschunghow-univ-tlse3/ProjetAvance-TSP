/*
 */

#include "tournee_canonique.h"
#include "affichage.h"

Resultat calcul_tournee_canonique(MatriceDistances matrice)
{
    size_t nombre_points = nombre_points_matrice(matrice);

    Resultat resultat;
    resultat.permutation = creer_permutation(nombre_points);
    resultat.distance = distance_totale_permutation(resultat.permutation, matrice);
    return resultat;
}
