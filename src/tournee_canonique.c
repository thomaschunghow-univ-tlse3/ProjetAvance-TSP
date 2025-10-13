/*
 */

#include "tournee_canonique.h"
#include "affichage.h"

Resultat calcul_tournee_canonique(MatriceDistances matrice)
{
    Resultat resultat;
    resultat.permutation = NULL; // TODO
    resultat.distance = 0;       // TODO
    size_t nombre_points = nombre_points_matrice(matrice);
    size_t nombre_distances = nombre_points - 1;
    TableauDistances tournee = creer_tableau_distances(nombre_distances, fonction_distance_matrice(matrice));
    for (size_t ligne = 0; ligne < nombre_distances; ligne++)
    {
        size_t colonne = ligne + 1;
        distance *distance_tournee = obtenir_element_tableau_distances(tournee, ligne);
        *distance_tournee = *obtenir_distance_matrice(matrice, ligne, colonne);
    }
    return resultat;
}
