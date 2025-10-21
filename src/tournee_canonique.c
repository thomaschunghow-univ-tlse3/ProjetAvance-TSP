/*
 */

#include "tournee_canonique.h"
#include "affichage.h"

Resultat calcul_tournee_canonique(MatriceDistance matrice)
{
    size_t nombre_points = matrice_nombre_points(matrice);

    Resultat resultat;
    resultat.permutation = creer_permutation(nombre_points);
    resultat.distance = distance_totale_permutation(resultat.permutation, matrice);
    return resultat;
}
