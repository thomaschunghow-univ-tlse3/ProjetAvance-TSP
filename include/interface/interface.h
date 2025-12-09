/*
 * interface.h
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "structure_matrice.h"

#include <stddef.h>

void interface_tournee_canonique(size_t nombre_points, size_t taille_point, void *tableau_points,

                                 size_t taille_distance, DistanceCalculer distance_calculer,

                                 size_t meilleure_permutation[], void *meilleure_longueur);

void interface_tournee_force_brute_naive(size_t nombre_points, size_t taille_point, void *tableau_points,

                                         size_t taille_distance, DistanceCalculer distance_calculer,
                                         DistanceAdditionner distance_additionner, DistanceComparer distance_comparer,

                                         size_t meilleure_permutation[], void *meilleure_longueur);

void interface_tournee_force_brute_avec_elagage(size_t nombre_points, size_t taille_point, void *tableau_points,

                                                size_t taille_distance, DistanceCalculer distance_calculer,
                                                DistanceAdditionner distance_additionner,
                                                DistanceComparer distance_comparer,

                                                size_t meilleure_permutation[], void *meilleure_longueur);

void interface_tournee_force_brute_incrementale(size_t nombre_points, size_t taille_point, void *tableau_points,

                                                size_t taille_distance, DistanceCalculer distance_calculer,
                                                DistanceAdditionner distance_additionner,
                                                DistanceSoustraire distance_soustraire,
                                                DistanceComparer distance_comparer,

                                                size_t meilleure_permutation[], void *meilleure_longueur);

void interface_tournee_2_optimisation_plus_proche_voisin(size_t nombre_points, size_t taille_point,
                                                         void *tableau_points,

                                                         size_t taille_distance, DistanceCalculer distance_calculer,
                                                         DistanceAdditionner distance_additionner,
                                                         DistanceSoustraire distance_soustraire,
                                                         DistanceComparer distance_comparer,

                                                         size_t meilleure_permutation[], void *meilleure_longueur);

void interface_tournee_2_optimisation_marche_aleatoire(size_t nombre_points, size_t taille_point, void *tableau_points,

                                                       size_t taille_distance, DistanceCalculer distance_calculer,
                                                       DistanceAdditionner distance_additionner,
                                                       DistanceSoustraire distance_soustraire,
                                                       DistanceComparer distance_comparer,

                                                       size_t meilleure_permutation[], void *meilleure_longueur);

void interface_tournee_genetique_light(size_t nombre_points, size_t taille_point, void *tableau_points,

                                       size_t taille_distance, DistanceCalculer distance_calculer,
                                       DistanceAdditionner distance_additionner, DistanceSoustraire distance_soustraire,
                                       DistanceComparer distance_comparer,

                                       size_t meilleure_permutation[], void *meilleure_longueur,

                                       size_t nombre_individus, size_t nombre_generations, double taux_mutation);

void interface_tournee_genetique_dpx(size_t nombre_points, size_t taille_point, void *tableau_points,

                                     size_t taille_distance, DistanceCalculer distance_calculer,
                                     DistanceAdditionner distance_additionner, DistanceSoustraire distance_soustraire,
                                     DistanceComparer distance_comparer,

                                     size_t meilleure_permutation[], void *meilleure_longueur,

                                     size_t nombre_individus, size_t nombre_generations, double taux_mutation);

#endif // INTERFACE_H
