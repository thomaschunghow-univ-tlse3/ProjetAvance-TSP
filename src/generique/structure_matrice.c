/*
 * structure_matrice.c
 */

#include "structure_matrice.h"

#include "structure_matrice_interne.h"

#include "nombre_aleatoire.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void size_t_echanger(size_t *A, size_t *B)
{
    size_t temp = *A;
    *A = *B;
    *B = temp;
}

size_t matrice_calculer_nombre_distances(size_t ligne)
{
    return (ligne * (ligne - 1)) / 2;
}

size_t matrice_calculer_indice(size_t ligne, size_t colonne)
{
    if (ligne < colonne)
    {
        size_t_echanger(&ligne, &colonne);
    }

    return matrice_calculer_nombre_distances(ligne) + colonne;
}

MatriceDistance matrice_creer(size_t nombre_points, size_t taille_point, size_t taille_distance,
                              DistanceCalculer distance_calculer, DistanceAdditionner distance_additionner,
                              DistanceSoustraire distance_soustraire, DistanceComparer distance_comparer)
{
    size_t nombre_distances = matrice_calculer_nombre_distances(nombre_points);

    MatriceDistance matrice =
        malloc(sizeof(struct matrice_distance) + nombre_points * taille_point + nombre_distances * taille_distance);

    if (matrice == NULL)
    {
        fprintf(stderr, "Erreur matrice_creer :\n"
                        "Échec de l'allocation mémoire de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    matrice->tableau_point.nombre_points = nombre_points;
    matrice->tableau_point.taille_point = taille_point;
    matrice->tableau_point.points = (char *)(matrice + 1);

    matrice->tableau_distance.nombre_distances = nombre_distances;
    matrice->tableau_distance.taille_distance = taille_distance;
    matrice->tableau_distance.distance_calculer = distance_calculer;
    matrice->tableau_distance.distance_additionner = distance_additionner;
    matrice->tableau_distance.distance_soustraire = distance_soustraire;
    matrice->tableau_distance.distance_comparer = distance_comparer;

    matrice->tableau_distance.distances = (char *)(matrice->tableau_point.points + nombre_points * taille_point);

    return matrice;
}

void matrice_supprimer(MatriceDistance *matrice)
{
    assert(matrice != NULL);
    assert(*matrice != NULL);

    free(*matrice);
    *matrice = NULL;
}

size_t matrice_obtenir_nombre_points(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_point.nombre_points;
}

size_t matrice_obtenir_taille_point(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_point.taille_point;
}

size_t matrice_obtenir_nombre_distances(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance.nombre_distances;
}

size_t matrice_obtenir_taille_distance(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance.taille_distance;
}

DistanceCalculer matrice_obtenir_distance_calculer(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance.distance_calculer;
}

DistanceAdditionner matrice_obtenir_distance_additionner(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance.distance_additionner;
}

DistanceSoustraire matrice_obtenir_distance_soustraire(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance.distance_soustraire;
}

DistanceComparer matrice_obtenir_distance_comparer(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance.distance_comparer;
}

void matrice_obtenir_point(MatriceDistance matrice, size_t indice, void *point_destination)
{
    assert(matrice != NULL);
    assert(indice < matrice_obtenir_nombre_points(matrice));

    size_t taille_point = matrice_obtenir_taille_point(matrice);

    memcpy(point_destination, matrice->tableau_point.points + indice * taille_point, taille_point);
}

void matrice_modifier_point(MatriceDistance matrice, size_t indice, void *point_source)
{
    assert(matrice != NULL);
    assert(indice < matrice_obtenir_nombre_points(matrice));

    size_t taille_point = matrice_obtenir_taille_point(matrice);

    memcpy(matrice->tableau_point.points + indice * taille_point, point_source, taille_point);
}

void matrice_obtenir_distance(MatriceDistance matrice, size_t ligne, size_t colonne, void *distance_destination)
{
    assert(matrice != NULL);
    assert(ligne < matrice_obtenir_nombre_points(matrice));
    assert(colonne < matrice_obtenir_nombre_points(matrice));

    if (ligne == colonne)
    {
        fprintf(stderr, "Erreur matrice_obtenir_distance :\n"
                        "La distance d'un point à lui-même est nulle.\n");
        exit(EXIT_FAILURE);
        /* Remarque : on ne connaît pas l'élément neutre du type de distance,
         * c'est pour cela qu'on ne peut pas renvoyer 0. */
    }

    if (ligne < colonne)
    {
        size_t_echanger(&ligne, &colonne);
    }

    size_t taille_distance = matrice_obtenir_taille_distance(matrice);

    size_t indice = matrice_calculer_indice(ligne, colonne);
    assert(indice < matrice_obtenir_nombre_distances(matrice));

    memcpy(distance_destination, matrice->tableau_distance.distances + indice * taille_distance, taille_distance);
}

void matrice_calculer_distance(MatriceDistance matrice, size_t ligne, size_t colonne)
{
    assert(matrice != NULL);
    assert(ligne < matrice_obtenir_nombre_points(matrice));
    assert(colonne < matrice_obtenir_nombre_points(matrice));

    if (ligne < colonne)
    {
        size_t_echanger(&ligne, &colonne);
    }

    size_t taille_point = matrice_obtenir_taille_point(matrice);

    char *point_ligne = matrice->tableau_point.points + ligne * taille_point;
    char *point_colonne = matrice->tableau_point.points + colonne * taille_point;

    size_t taille_distance = matrice_obtenir_taille_distance(matrice);
    DistanceCalculer distance_calculer = matrice_obtenir_distance_calculer(matrice);

    size_t indice = matrice_calculer_indice(ligne, colonne);
    assert(indice < matrice_obtenir_nombre_distances(matrice));

    char *distance = matrice->tableau_distance.distances + indice * taille_distance;

    distance_calculer(point_ligne, point_colonne, distance);
}

void matrice_remplir(MatriceDistance matrice)
{
    assert(matrice != NULL);

    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    for (size_t ligne = 0; ligne < nombre_points; ligne++)
    {
        for (size_t colonne = 0; colonne < ligne; colonne++)
        {
            matrice_calculer_distance(matrice, ligne, colonne);
        }
    }
}

int matrice_comparer_distances(MatriceDistance matrice, size_t ligne_A, size_t colonne_A, size_t ligne_B,
                               size_t colonne_B)
{
    assert(matrice != NULL);
    assert(ligne_A < matrice_obtenir_nombre_points(matrice));
    assert(colonne_A < matrice_obtenir_nombre_points(matrice));
    assert(ligne_B < matrice_obtenir_nombre_points(matrice));
    assert(colonne_B < matrice_obtenir_nombre_points(matrice));

    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);
    size_t taille_distance = matrice_obtenir_taille_distance(matrice);

    size_t indice_A = matrice_calculer_indice(ligne_A, colonne_A);
    size_t indice_B = matrice_calculer_indice(ligne_B, colonne_B);

    return distance_comparer(matrice->tableau_distance.distances + indice_A * taille_distance,
                             matrice->tableau_distance.distances + indice_B * taille_distance);
}
