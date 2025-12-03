/*
 * conversion.c
 */

#include "structure_matrice.h"
#include "structure_permutation.h"
#include "tournee_2_optimisation.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"
#include "tournee_genetique.h"

#include <stdlib.h>

MatriceDistance interface_importer_matrice(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_point,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer)
{
    MatriceDistance matrice = matrice_creer(
        nombre_points,
        taille_point,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    for (size_t i = 0; i < nombre_points; i++)
    {
        matrice_modifier_point(matrice, i, (char *)tableau_point + i * taille_point);
    }

    matrice_remplir(matrice);

    return matrice;
}

void interface_exporter_permutation(
    Permutation permutation,
    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        meilleure_permutation[i] = permutation_obtenir_sommet(permutation, i);
    }

    permutation_obtenir_longueur(permutation, meilleure_longueur);
}

void interface_tournee_canonique(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_canonique(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_force_brute_naive(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_force_brute_naive(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_force_brute_avec_elagage(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_force_brute_avec_elagage(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_force_brute_incrementale(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_force_brute_incrementale(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_plus_proche_voisin(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_plus_proche_voisin(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_marche_aleatoire(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_marche_aleatoire(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_2_optimisation_plus_proche_voisin(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_2_optimisation_plus_proche_voisin(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_2_optimisation_marche_aleatoire(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_2_optimisation_marche_aleatoire(matrice);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_genetique_light(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur,

    size_t nombre_individus,
    size_t nombre_generations,
    double taux_mutation)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_genetique_light(
        matrice,
        nombre_individus,
        nombre_generations,
        taux_mutation,
        nombre_individus / 2);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_genetique_dpx(
    size_t nombre_points,
    size_t taille_point,
    void *tableau_points,

    size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer,

    size_t *meilleure_permutation,
    void *meilleure_longueur,

    size_t nombre_individus,
    size_t nombre_generations,
    double taux_mutation)
{
    MatriceDistance matrice = interface_importer_matrice(
        nombre_points,
        taille_point,
        tableau_points,
        taille_distance,
        distance_calculer,
        distance_additionner,
        distance_soustraire,
        distance_comparer);

    Permutation permutation = tournee_genetique_dpx(
        matrice,
        nombre_individus,
        nombre_generations,
        taux_mutation,
        nombre_individus / 2);

    interface_exporter_permutation(
        permutation,
        meilleure_permutation,
        meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}
