/*
 * structure_matrice.c
 */

#include "options.h"
#include "structure_matrice.h"

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

struct matrice_distance
{
    TableauPoint tableau_points;
    TableauDistance tableau_distances;
	MethodeCalcul methode;
};

void echanger(size_t *ligne, size_t *colonne)
{
    size_t temp = *ligne;
    *ligne = *colonne;
    *colonne = temp;
}

size_t matrice_calculer_nombre_distances(size_t ligne)
{
    return (ligne * (ligne - 1)) / 2;
}

size_t matrice_obtenir_indice(size_t ligne, size_t colonne)
{
    return matrice_calculer_nombre_distances(ligne) + colonne;
}

void matrice_assert_non_vide(MatriceDistance matrice)
{
    assert(matrice != NULL);
    (void)matrice;
}

void matrice_assert_indice_valide(size_t taille_points, size_t ligne, size_t colonne)
{
    assert(ligne < taille_points && colonne < taille_points);
    (void)taille_points;
    (void)ligne;
    (void)colonne;
}

TableauPoint matrice_obtenir_tableau_point(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);

    return matrice->tableau_points;
}

TableauDistance matrice_obtenir_tableau_distance(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);

    return matrice->tableau_distances;
}

Point *matrice_obtenir_adresse_point(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);
    return tableau_point_obtenir_tableau(matrice_obtenir_tableau_point(matrice));
}

Point *matrice_obtenir_adresse_point(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);
    return tableau_point_obtenir_tableau(matrice_obtenir_tableau_point(matrice));
}

void matrice_calculer_distance(MatriceDistance matrice, size_t ligne, size_t colonne)
{
    matrice_assert_non_vide(matrice);

    matrice_assert_indice_valide(matrice_obtenir_nombre_points(matrice), ligne, colonne);

    TableauPoint points = matrice_obtenir_tableau_point(matrice);
    TableauDistance distances = matrice_obtenir_tableau_distance(matrice);
    FonctionCalcul calculer_distance = tableau_distance_obtenir_fonction_calcul(distances);

    matrice_assert_indice_valide(tableau_point_obtenir_taille(points), ligne, colonne);

    Point point_ligne = tableau_point_obtenir_point(points, ligne);
    Point point_colonne = tableau_point_obtenir_point(points, colonne);

    distance distance_calculee = calculer_distance(point_ligne, point_colonne);

    tableau_distance_modifier_distance(distances, matrice_obtenir_indice(ligne, colonne), distance_calculee);
}



void matrice_remplir_distance(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);
	/*MethodeCalcul methode = matrice -> methode;
	if(methode == PLUS_PROCHE_VOISIN_2_OPTIMISATION || methode == MARCHE_ALEATOIRE_2_OPTIMISATION)
		recherche_croisement(matrice);//classement des arêtes*/
	
    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    for (size_t ligne = 0; ligne < nombre_points; ligne++)
    {
        for (size_t colonne = 0; colonne < ligne; colonne++)
        {
            matrice_calculer_distance(matrice, ligne, colonne);
        }
    }
}

MatriceDistance matrice_creer(size_t nombre_points, FonctionCalcul calculer_distance, MethodeCalcul methode)
{
    MatriceDistance matrice = malloc(sizeof(struct matrice_distance));

    if (matrice == NULL)
    {
        fprintf(stderr,
                "Erreur matrice_creer :\n"
                "Echec de l'allocation mémoire de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    matrice->tableau_points = tableau_point_creer(nombre_points);
    size_t nombre_distances = matrice_calculer_nombre_distances(nombre_points);
	
    matrice->tableau_distances = tableau_distance_creer(nombre_distances, calculer_distance);
	matrice->methode = methode;
	
    return matrice;
}

void matrice_supprimer(MatriceDistance *matrice)
{
    matrice_assert_non_vide(*matrice);

    TableauPoint points = matrice_obtenir_tableau_point(*matrice);
    TableauDistance distances = matrice_obtenir_tableau_distance(*matrice);

    tableau_point_supprimer(&points);
    tableau_distance_supprimer(&distances);
	
    free(*matrice);
    *matrice = NULL;
}

size_t matrice_obtenir_nombre_points(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);

    return tableau_point_obtenir_taille(matrice_obtenir_tableau_point(matrice));
}

size_t matrice_obtenir_nombre_distances(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);

    return tableau_distance_obtenir_taille(matrice_obtenir_tableau_distance(matrice));
}

FonctionCalcul matrice_obtenir_fonction_calcul(MatriceDistance matrice)
{
    matrice_assert_non_vide(matrice);

    return tableau_distance_obtenir_fonction_calcul(matrice_obtenir_tableau_distance(matrice));
}

Point matrice_obtenir_point(MatriceDistance matrice, size_t indice)
{
    matrice_assert_non_vide(matrice);

    TableauPoint points = matrice_obtenir_tableau_point(matrice);

    return tableau_point_obtenir_point(points, indice);
}

distance matrice_obtenir_distance(MatriceDistance matrice, size_t ligne, size_t colonne)
{
    matrice_assert_non_vide(matrice);

    TableauPoint points = matrice_obtenir_tableau_point(matrice);
    TableauDistance distances = matrice_obtenir_tableau_distance(matrice);

    matrice_assert_indice_valide(tableau_point_obtenir_taille(points), ligne, colonne);

    if (ligne == colonne)
    {
        return 0;
    }

    if (ligne < colonne)
    {
        echanger(&ligne, &colonne);
    }

    return tableau_distance_obtenir_distance(distances, matrice_obtenir_indice(ligne, colonne));
}
