/*
 * conversion.c
 */

#include "interface.h"

#include "structure_matrice.h"
#include "structure_permutation.h"
#include "tournee_2_optimisation.h"
#include "tournee_force_brute.h"
#include "tournee_genetique.h"

#include <stdlib.h>

MatriceDistance interface_importer_matrice(size_t nombre_points, size_t taille_point, void *tableau_point,

                                           size_t taille_distance, DistanceCalculer distance_calculer,
                                           DistanceAdditionner distance_additionner,
                                           DistanceSoustraire distance_soustraire, DistanceComparer distance_comparer)
{
    MatriceDistance matrice = matrice_creer(nombre_points, taille_point, taille_distance, distance_calculer,
                                            distance_additionner, distance_soustraire, distance_comparer);

    for (size_t i = 0; i < nombre_points; i++)
    {
        matrice_modifier_point(matrice, i, (char *)tableau_point + i * taille_point);
    }

    matrice_remplir(matrice);

    return matrice;
}

void interface_exporter_permutation(Permutation permutation, size_t *meilleure_permutation, void *meilleure_longueur)
{
    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        meilleure_permutation[i] = permutation_obtenir_sommet(permutation, i);
    }

    permutation_obtenir_longueur(permutation, meilleure_longueur);
}

void interface_tournee_canonique(size_t nombre_points, size_t taille_point, void *tableau_points,

                                 size_t taille_distance, DistanceCalculer distance_calculer,

                                 size_t meilleure_permutation[], void *meilleure_longueur)
{
    MatriceDistance matrice = interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance,
                                                         distance_calculer, NULL, NULL, NULL);

    Permutation permutation = permutation_creer(nombre_points, taille_distance);

    tournee_canonique(matrice, permutation);

    interface_exporter_permutation(permutation, meilleure_permutation, meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation);
}

void interface_tournee_force_brute_naive(size_t nombre_points, size_t taille_point, void *tableau_points,

                                         size_t taille_distance, DistanceCalculer distance_calculer,
                                         DistanceAdditionner distance_additionner, DistanceComparer distance_comparer,

                                         size_t meilleure_permutation[], void *meilleure_longueur)
{
    MatriceDistance matrice =
        interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance, distance_calculer,
                                   distance_additionner, NULL, distance_comparer);

    Permutation permutation_courante = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_minimale = permutation_creer(nombre_points, taille_distance);

    tournee_force_brute_naive(matrice, permutation_courante, permutation_minimale);

    interface_exporter_permutation(permutation_minimale, meilleure_permutation, meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation_minimale);
    permutation_supprimer(&permutation_courante);
}

void interface_tournee_force_brute_avec_elagage(size_t nombre_points, size_t taille_point, void *tableau_points,

                                                size_t taille_distance, DistanceCalculer distance_calculer,
                                                DistanceAdditionner distance_additionner,
                                                DistanceComparer distance_comparer,

                                                size_t meilleure_permutation[], void *meilleure_longueur)
{
    MatriceDistance matrice =
        interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance, distance_calculer,
                                   distance_additionner, NULL, distance_comparer);

    Permutation permutation_courante = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_minimale = permutation_creer(nombre_points, taille_distance);

    tournee_force_brute_avec_elagage(matrice, permutation_courante, permutation_minimale);

    interface_exporter_permutation(permutation_minimale, meilleure_permutation, meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation_minimale);
    permutation_supprimer(&permutation_courante);
}

void interface_tournee_force_brute_incrementale(size_t nombre_points, size_t taille_point, void *tableau_points,

                                                size_t taille_distance, DistanceCalculer distance_calculer,
                                                DistanceAdditionner distance_additionner,
                                                DistanceSoustraire distance_soustraire,
                                                DistanceComparer distance_comparer,

                                                size_t meilleure_permutation[], void *meilleure_longueur)
{
    MatriceDistance matrice =
        interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance, distance_calculer,
                                   distance_additionner, distance_soustraire, distance_comparer);

    Permutation permutation_courante = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_minimale = permutation_creer(nombre_points, taille_distance);

    tournee_force_brute_incrementale(matrice, permutation_courante, permutation_minimale);

    interface_exporter_permutation(permutation_minimale, meilleure_permutation, meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation_minimale);
    permutation_supprimer(&permutation_courante);
}

void interface_tournee_2_optimisation_plus_proche_voisin(size_t nombre_points, size_t taille_point,
                                                         void *tableau_points,

                                                         size_t taille_distance, DistanceCalculer distance_calculer,
                                                         DistanceAdditionner distance_additionner,
                                                         DistanceSoustraire distance_soustraire,
                                                         DistanceComparer distance_comparer,

                                                         size_t meilleure_permutation[], void *meilleure_longueur)
{
    MatriceDistance matrice =
        interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance, distance_calculer,
                                   distance_additionner, distance_soustraire, distance_comparer);

    Permutation permutation_courante = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_resultat = permutation_creer(nombre_points, taille_distance);

    tournee_2_optimisation_plus_proche_voisin(matrice, permutation_courante, permutation_resultat);

    interface_exporter_permutation(permutation_resultat, meilleure_permutation, meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation_resultat);
    permutation_supprimer(&permutation_courante);
}

void interface_tournee_2_optimisation_marche_aleatoire(size_t nombre_points, size_t taille_point, void *tableau_points,

                                                       size_t taille_distance, DistanceCalculer distance_calculer,
                                                       DistanceAdditionner distance_additionner,
                                                       DistanceSoustraire distance_soustraire,
                                                       DistanceComparer distance_comparer,

                                                       size_t meilleure_permutation[], void *meilleure_longueur)
{
    MatriceDistance matrice =
        interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance, distance_calculer,
                                   distance_additionner, distance_soustraire, distance_comparer);

    Permutation permutation_courante = permutation_creer(nombre_points, taille_distance);
    Permutation permutation_resultat = permutation_creer(nombre_points, taille_distance);

    tournee_2_optimisation_marche_aleatoire(matrice, permutation_courante, permutation_resultat);

    interface_exporter_permutation(permutation_resultat, meilleure_permutation, meilleure_longueur);

    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation_resultat);
    permutation_supprimer(&permutation_courante);
}

void interface_tournee_genetique_light(size_t nombre_points, size_t taille_point, void *tableau_points,

                                       size_t taille_distance, DistanceCalculer distance_calculer,
                                       DistanceAdditionner distance_additionner, DistanceSoustraire distance_soustraire,
                                       DistanceComparer distance_comparer,

                                       size_t meilleure_permutation[], void *meilleure_longueur,

                                       size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    Permutation permutation_resultat = permutation_creer(nombre_points, taille_distance);

    TableauPermutation population = tableau_permutation_creer(nombre_individus, nombre_points, taille_distance);
    TableauPermutation enfants = tableau_permutation_creer(nombre_individus, nombre_points, taille_distance);
    TableauPermutation parents = tableau_permutation_creer(nombre_individus, nombre_points, taille_distance);
    Permutation inverse = permutation_creer(nombre_points, taille_distance);

    MatriceDistance matrice =
        interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance, distance_calculer,
                                   distance_additionner, distance_soustraire, distance_comparer);

    tournee_genetique_light(matrice, nombre_individus, nombre_generations, taux_mutation, nombre_individus / 2,
                            permutation_resultat, population, enfants, parents, inverse);

    interface_exporter_permutation(permutation_resultat, meilleure_permutation, meilleure_longueur);

    tableau_permutation_supprimer(&population);
    tableau_permutation_supprimer(&enfants);
    tableau_permutation_supprimer(&parents);
    permutation_supprimer(&inverse);
    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation_resultat);
}

void interface_tournee_genetique_dpx(size_t nombre_points, size_t taille_point, void *tableau_points,

                                     size_t taille_distance, DistanceCalculer distance_calculer,
                                     DistanceAdditionner distance_additionner, DistanceSoustraire distance_soustraire,
                                     DistanceComparer distance_comparer,

                                     size_t meilleure_permutation[], void *meilleure_longueur,

                                     size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    Permutation permutation_resultat = permutation_creer(nombre_points, taille_distance);

    TableauPermutation population = tableau_permutation_creer(nombre_individus, nombre_points, taille_distance);
    TableauPermutation enfants = tableau_permutation_creer(nombre_individus, nombre_points, taille_distance);
    TableauPermutation parents = tableau_permutation_creer(nombre_individus, nombre_points, taille_distance);
    Permutation inverse = permutation_creer(nombre_points, taille_distance);
    TableauMorceau morceaux = tableau_morceau_creer(nombre_points + 1);

    MatriceDistance matrice =
        interface_importer_matrice(nombre_points, taille_point, tableau_points, taille_distance, distance_calculer,
                                   distance_additionner, distance_soustraire, distance_comparer);

    tournee_genetique_dpx(matrice, nombre_individus, nombre_generations, taux_mutation, nombre_individus / 2,
                          permutation_resultat, population, enfants, parents, inverse, morceaux);

    interface_exporter_permutation(permutation_resultat, meilleure_permutation, meilleure_longueur);

    tableau_morceau_supprimer(&morceaux);
    tableau_permutation_supprimer(&population);
    tableau_permutation_supprimer(&enfants);
    tableau_permutation_supprimer(&parents);
    permutation_supprimer(&inverse);
    matrice_supprimer(&matrice);
    permutation_supprimer(&permutation_resultat);
}
