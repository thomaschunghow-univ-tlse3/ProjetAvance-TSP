/*
 *
 */

#include "canonique.h"

TableauDistances tournee_canonique(MatriceDistances matrice)
{
    size_t taille_points = taille_tableau_points(tableau_points_matrice(matrice));
    TableauDistances tournee = creer_tableau_distances(taille_points - 1, fonction_tableau_distances(tableau_distances_matrice(matrice)));
    for (size_t ligne = 0; ligne < taille_points - 1; ligne++)
    {
        size_t colonne = ligne + 1;
        calculer_element_matrice(matrice, ligne, colonne);
        distance *distance_tournee = obtenir_element_tableau_distances(tournee, ligne);
        *distance_tournee = *obtenir_distance_matrice(matrice, ligne, colonne);
    }
    return tournee;
}
