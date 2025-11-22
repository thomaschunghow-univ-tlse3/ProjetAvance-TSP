/*
 * tournee_canonique.c
 */

#include "tournee_canonique.h"
#include "affichage.h"

Resultat tournee_canonique(MatriceDistance matrice)
{
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    Resultat resultat;
    resultat.permutation = permutation_creer(nombre_points);
    resultat.longueur = permutation_calculer_longueur(resultat.permutation, matrice);

    return resultat;
}
