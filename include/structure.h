/*
 * structure.h
 */

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdbool.h>
#include <stddef.h>

void size_t_echanger(size_t *A, size_t *B);

/*
 * Point :
 * Définition et opérations du type abstrait générique de tableau de point.
 */

typedef struct tableau_point *TableauPoint;
/*
 * Distance :
 * Définition et opérations du type abstrait générique de tableau de distance.
 */

typedef struct tableau_distance *TableauDistance;

typedef void (*DistanceCalculer)(void *point_A, void *point_B, void *distance);
typedef void (*DistanceAdditionner)(void *distance_A, void *distance_B, void *somme);
typedef void (*DistanceSoustraire)(void *distance_A, void *distance_B, void *difference);
/* Retourne une valeur inférieure à 0 si distance_A < distance_B,
 * retourne 0 si distance_A == distance_B,
 * retourne une valeur supérieure à 0 si distance_A > distance_B. */
typedef int (*DistanceComparer)(void *distance_A, void *distance_B);

/*
 * Matrice :
 * Définition et opérations du type abstrait de demi-matrice de distance.
 *
 * Pour économiser de la mémoire,
 * seule la partie triangulaire inférieure de la matrice
 * est stockée dans le tableau de distance (sans la diagonale, car nulle).
 *
 * Remarque : pour alléger le code et les noms des fonctions,
 * nous utilisons le mot "matrice" pour désigner une demi-matrice.
 * En pratique, toutes les matrices manipulées ici sont des demi-matrices.
 */

typedef struct matrice_distance *MatriceDistance;

MatriceDistance matrice_creer(
    size_t nombre_points, size_t taille_point, size_t taille_distance,
    DistanceCalculer distance_calculer,
    DistanceAdditionner distance_additionner,
    DistanceSoustraire distance_soustraire,
    DistanceComparer distance_comparer);
void matrice_supprimer(MatriceDistance *);

size_t matrice_obtenir_nombre_points(MatriceDistance);
size_t matrice_obtenir_taille_point(MatriceDistance matrice);

size_t matrice_obtenir_nombre_distances(MatriceDistance);
size_t matrice_obtenir_taille_distance(MatriceDistance matrice);

DistanceCalculer matrice_obtenir_distance_calculer(MatriceDistance);
DistanceAdditionner matrice_obtenir_distance_additionner(MatriceDistance matrice);
DistanceSoustraire matrice_obtenir_distance_soustraire(MatriceDistance matrice);
DistanceComparer matrice_obtenir_distance_comparer(MatriceDistance matrice);

void matrice_obtenir_point(MatriceDistance, size_t indice, void *point_destination);
void matrice_modifier_point(MatriceDistance, size_t indice, void *point_destination);

void matrice_obtenir_distance(MatriceDistance, size_t ligne, size_t colonne, void *distance_destination);
void matrice_remplir(MatriceDistance);

int matrice_comparer_distances(MatriceDistance, size_t ligne_A, size_t colonne_A, size_t ligne_B, size_t colonne_B);

/*
 * Permutation :
 * Définition et opérations du type abstrait de permutation.
 *
 * Remarque : les permutations sont initialisées dans l’ordre canonique,
 * puis parcourues dans l’ordre lexical, en fixant le premier indice.
 * C'est-à-dire, on calcule les (n-1)! permutations, et non pas les n! permutations,
 * car comparer toutes les tournées revient à comparer toutes les tournées qui partent du même point.
 *
 * La permutation est également associée à sa longueur.
 * Cependant, la longueur peut ne plus être valide après certaines opérations.
 * Il faut porter attention à initialiser correctement la longueur,
 * et à la mettre à jour après une opération qui modifie la permutation.
 */

typedef struct permutation *Permutation;

Permutation permutation_creer(size_t nombre_sommets, size_t taille_distance);
void permutation_supprimer(Permutation *);

void permutation_initialiser(Permutation);
void permutation_melanger(Permutation);
void permutation_inverser(Permutation, Permutation inverse);
void permutation_decaler(Permutation, size_t nombre_decalage_gauche);

void permutation_copier(Permutation destination, Permutation source);

size_t permutation_obtenir_nombre_sommets(Permutation);

size_t permutation_obtenir_sommet(Permutation, size_t indice);
void permutation_echanger_sommets(Permutation permutation, size_t sommet_A, size_t sommet_B);

size_t permutation_obtenir_taille_distance(Permutation);

void permutation_obtenir_longueur(Permutation, void *longueur_destination);
void permutation_modifier_longueur(Permutation, void *longueur_source);

int permutation_comparer_longueurs(Permutation permutation_A, Permutation permutation_B, DistanceComparer);

void permutation_calculer_longueur(
    Permutation permutation, MatriceDistance matrice);
void permutation_calculer_longueur_avec_elagage(
    Permutation permutation, MatriceDistance matrice, Permutation permutation_minimale);

bool permutation_avancer(Permutation);
bool permutation_avancer_et_incrementer_longueur(
    Permutation permutation, MatriceDistance matrice);

void permutation_echanger_aretes(Permutation, size_t sommet_A, size_t sommet_B);
void permutation_calculer_difference_apres_decroisement(
    MatriceDistance matrice, Permutation permutation,
    size_t sommet_A, size_t sommet_B, Permutation permutation_decroisee);

/*
 * Tableau de permutation :
 * Définition et opérations du type abstrait de tableau de permutation.
 */

typedef struct tableau_permutation *TableauPermutation;

TableauPermutation tableau_permutation_creer(size_t nombre_permutations, size_t nombre_sommets, size_t taille_distance);
void tableau_permutation_supprimer(TableauPermutation *);

size_t tableau_permutation_obtenir_nombre_permutations(TableauPermutation);

/* Ici on brise l'abstraction par souci d'optimisation.
 * On obtient l'adresse de la permutation réelle du tableau, et non pas une copie.
 * On peut donc la modifier directement. */
Permutation tableau_permutation_obtenir_permutation(TableauPermutation, size_t indice);
void tableau_permutation_obtenir_longueur(TableauPermutation, size_t indice, void *longueur_destination);
void tableau_permutation_modifier_longueur(TableauPermutation, size_t indice, void *longueur_source);

size_t tableau_permutation_trouver_pire_individu(TableauPermutation, DistanceComparer);
size_t tableau_permutation_trouver_meilleur_individu(TableauPermutation, DistanceComparer);

void tableau_permutation_echanger_tableaux(TableauPermutation *tableau_A, TableauPermutation *tableau_B);

void tableau_permutation_trier(TableauPermutation, DistanceComparer);

#endif // STRUCTURE_H
