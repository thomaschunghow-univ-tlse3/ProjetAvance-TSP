/*
 * structure.c
 */

#include "structure.h"

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

/*
 * Point.
 */

struct tableau_point
{
    size_t nombre_points;
    size_t taille_point;

    char *points;
    /* On utilise le type char pour pouvoir faire de l'arithmétique de pointeurs,
     * car void n'a pas de taille. */
};

TableauPoint tableau_point_creer(size_t nombre_points, size_t taille_point)
{
    TableauPoint tableau = malloc(sizeof(struct tableau_point) + nombre_points * taille_point);

    if (tableau == NULL)
    {
        fprintf(
            stderr,
            "Erreur tableau_point_creer :\n"
            "Échec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }

    tableau->nombre_points = nombre_points;
    tableau->taille_point = taille_point;

    tableau->points = (char *)(tableau + 1);

    return tableau;
}

void tableau_point_supprimer(TableauPoint *tableau)
{
    assert(tableau != NULL);
    assert(*tableau != NULL);

    free(*tableau);
    *tableau = NULL;
}

size_t tableau_point_obtenir_nombre_points(TableauPoint tableau)
{
    assert(tableau != NULL);

    return tableau->nombre_points;
}

size_t tableau_point_obtenir_taille_point(TableauPoint tableau)
{
    assert(tableau != NULL);

    return tableau->taille_point;
}

void tableau_point_obtenir_point(TableauPoint tableau, size_t indice, void *point_destination)
{
    assert(tableau != NULL);
    assert(indice < tableau_point_obtenir_nombre_points(tableau));
    assert(point_destination != NULL);

    size_t taille_point = tableau->taille_point;

    memcpy(point_destination, tableau->points + indice * taille_point, taille_point);
}

void tableau_point_modifier_point(TableauPoint tableau, size_t indice, void *point_source)
{
    assert(tableau != NULL);
    assert(indice < tableau_point_obtenir_nombre_points(tableau));
    assert(point_source != NULL);

    size_t taille_point = tableau->taille_point;

    memcpy(tableau->points + indice * taille_point, point_source, taille_point);
}

/*
 * Distance.
 */

struct tableau_distance
{
    size_t nombre_distances;
    size_t taille_distance;

    DistanceCalculer distance_calculer;

    char *distances;
    /* On utilise le type char pour pouvoir faire de l'arithmétique de pointeurs,
     * car void n'a pas de taille. */
};

TableauDistance tableau_distance_creer(
    size_t nombre_distances, size_t taille_distance, DistanceCalculer distance_calculer)
{
    TableauDistance tableau = malloc(
        sizeof(struct tableau_distance) + nombre_distances * taille_distance);

    if (tableau == NULL)
    {
        fprintf(
            stderr,
            "Erreur tableau_distance_creer :\n"
            "Échec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }

    tableau->nombre_distances = nombre_distances;
    tableau->taille_distance = taille_distance;
    tableau->distance_calculer = distance_calculer;

    tableau->distances = (char *)(tableau + 1);

    return tableau;
}

void tableau_distance_supprimer(TableauDistance *tableau)
{
    assert(tableau != NULL);
    assert(*tableau != NULL);

    free(*tableau);
    *tableau = NULL;
}

size_t tableau_distance_obtenir_nombre_distances(TableauDistance tableau)
{
    assert(tableau != NULL);

    return tableau->nombre_distances;
}

size_t tableau_distance_obtenir_taille_distance(TableauDistance tableau)
{
    assert(tableau != NULL);

    return tableau->taille_distance;
}

DistanceCalculer tableau_distance_obtenir_distance_calculer(TableauDistance tableau)
{
    assert(tableau != NULL);

    return tableau->distance_calculer;
}

void tableau_distance_obtenir_distance(
    TableauDistance tableau, size_t indice, void *distance_destination)
{
    assert(tableau != NULL);
    assert(indice < tableau_distance_obtenir_nombre_distances(tableau));
    assert(distance_destination != NULL);

    size_t taille_distance = tableau->taille_distance;

    memcpy(distance_destination, tableau->distances + indice * taille_distance, taille_distance);
}

void tableau_distance_modifier_distance(
    TableauDistance tableau, size_t indice, void *distance_source)
{
    assert(tableau != NULL);
    assert(indice < tableau_distance_obtenir_nombre_distances(tableau));
    assert(distance_source != NULL);

    size_t taille_distance = tableau->taille_distance;

    memcpy(tableau->distances + indice * taille_distance, distance_source, taille_distance);
}

/*
 * Matrice.
 */

struct matrice_distance
{
    struct tableau_point *tableau_point;
    struct tableau_distance *tableau_distance;
};

size_t matrice_calculer_nombre_distances(size_t ligne)
{
    return (ligne * (ligne - 1)) / 2;
}

size_t matrice_calculer_indice(size_t ligne, size_t colonne)
{
    return matrice_calculer_nombre_distances(ligne) + colonne;
}

MatriceDistance matrice_creer(
    size_t nombre_points, size_t taille_point,
    size_t taille_distance, DistanceCalculer distance_calculer)
{
    MatriceDistance matrice = malloc(sizeof(struct matrice_distance));

    if (matrice == NULL)
    {
        fprintf(
            stderr,
            "Erreur matrice_creer :\n"
            "Échec de l'allocation mémoire de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    matrice->tableau_point = tableau_point_creer(nombre_points, taille_point);

    size_t nombre_distances = matrice_calculer_nombre_distances(nombre_points);
    matrice->tableau_distance = tableau_distance_creer(nombre_distances, taille_distance, distance_calculer);

    return matrice;
}

void matrice_supprimer(MatriceDistance *matrice)
{
    assert(matrice != NULL);
    assert(*matrice != NULL);

    TableauPoint tableau_point = (*matrice)->tableau_point;
    TableauDistance tableau_distance = (*matrice)->tableau_distance;

    tableau_point_supprimer(&tableau_point);
    tableau_distance_supprimer(&tableau_distance);

    free(*matrice);
    *matrice = NULL;
}

size_t matrice_obtenir_nombre_points(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_point->nombre_points;
}

size_t matrice_obtenir_taille_point(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_point->taille_point;
}

size_t matrice_obtenir_nombre_distances(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance->nombre_distances;
}

size_t matrice_obtenir_taille_distance(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance->taille_distance;
}

DistanceCalculer matrice_obtenir_distance_calculer(MatriceDistance matrice)
{
    assert(matrice != NULL);

    return matrice->tableau_distance->distance_calculer;
}

void matrice_obtenir_point(MatriceDistance matrice, size_t indice, void *point_destination)
{
    assert(matrice != NULL);

    TableauPoint tableau_point = matrice->tableau_point;

    tableau_point_obtenir_point(tableau_point, indice, point_destination);
}

void matrice_modifier_point(MatriceDistance matrice, size_t indice, void *point_source)
{
    assert(matrice != NULL);

    TableauPoint tableau_point = matrice->tableau_point;

    tableau_point_modifier_point(tableau_point, indice, point_source);
}

void matrice_obtenir_distance(
    MatriceDistance matrice, size_t ligne, size_t colonne, void *distance_destination)
{
    assert(matrice != NULL);

    TableauPoint tableau_point = matrice->tableau_point;

    size_t nombre_points = tableau_point->nombre_points;

    assert(ligne < nombre_points);
    assert(colonne < nombre_points);

    TableauDistance tableau_distance = matrice->tableau_distance;

    if (ligne == colonne)
    {
        fprintf(
            stderr,
            "Erreur matrice_obtenir_distance :\n"
            "La distance d'un point à lui-même est nulle.\n");
        exit(EXIT_FAILURE);
        /* Remarque : on ne connaît pas l'élément neutre du type distance,
         * c'est pour cela qu'on ne peut pas renvoyer 0. */
    }

    if (ligne < colonne)
    {
        size_t_echanger(&ligne, &colonne);
    }

    size_t indice = matrice_calculer_indice(ligne, colonne);

    tableau_distance_obtenir_distance(tableau_distance, indice, distance_destination);
}

void matrice_calculer_distance(MatriceDistance matrice, size_t ligne, size_t colonne)
{
    assert(matrice != NULL);

    TableauPoint tableau_point = matrice->tableau_point;
    size_t nombre_points = tableau_point->nombre_points;
    size_t taille_point = tableau_point->taille_point;

    assert(ligne < nombre_points);
    assert(colonne < nombre_points);

    if (ligne < colonne)
    {
        size_t_echanger(&ligne, &colonne);
    }

    char *point_ligne = tableau_point->points + ligne * taille_point;
    char *point_colonne = tableau_point->points + colonne * taille_point;

    TableauDistance tableau_distance = matrice->tableau_distance;
    size_t nombre_distances = tableau_distance->nombre_distances;
    size_t taille_distance = tableau_distance->taille_distance;
    DistanceCalculer distance_calculer = tableau_distance->distance_calculer;

    size_t indice = matrice_calculer_indice(ligne, colonne);

    assert(indice < nombre_distances);

    char *distance = tableau_distance->distances + indice * taille_distance;

    distance_calculer(point_ligne, point_colonne, distance);
}

void matrice_remplir(MatriceDistance matrice)
{
    assert(matrice != NULL);

    size_t nombre_points = matrice->tableau_point->nombre_points;

    for (size_t ligne = 0; ligne < nombre_points; ligne++)
    {
        for (size_t colonne = 0; colonne < ligne; colonne++)
        {
            matrice_calculer_distance(matrice, ligne, colonne);
        }
    }
}

/*
 * Permutation.
 */

struct permutation
{
    size_t nombre_sommets;
    size_t *sommets;

    size_t taille_distance;
    char *longueur;
    /* On utilise le type char pour pouvoir faire de l'arithmétique de pointeurs,
     * car void n'a pas de taille. */
};

Permutation permutation_creer(size_t nombre_sommets, size_t taille_distance)
{
    Permutation permutation = malloc(
        sizeof(struct permutation) +
        nombre_sommets * sizeof(size_t) +
        taille_distance);

    if (permutation == NULL)
    {
        fprintf(
            stderr,
            "Erreur permutation_creer :\n"
            "Échec de l'allocation mémoire de la permutation.\n");
        exit(EXIT_FAILURE);
    }

    permutation->nombre_sommets = nombre_sommets;
    permutation->sommets = (size_t *)(permutation + 1);

    permutation->taille_distance = taille_distance;
    permutation->longueur = (char *)(permutation->sommets + nombre_sommets);

    permutation_initialiser(permutation);

    return permutation;
}

void permutation_supprimer(Permutation *permutation)
{
    assert(permutation != NULL);
    assert(*permutation != NULL);

    free(*permutation);
    *permutation = NULL;
}

void permutation_initialiser(Permutation permutation)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    size_t *sommets = permutation->sommets;

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        sommets[i] = i;
    }
}

void permutation_melanger(Permutation permutation)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;

    for (size_t sommet = 0; sommet < nombre_sommets - 1; sommet++)
    {
        size_t voisin = donner_entier_aleatoire(sommet, nombre_sommets);

        permutation_echanger_sommets(permutation, sommet, voisin);
    }
}

/* Inverse au sens mathématique. C'est-à-dire, la position du sommet de valeur i dans la permutation
 * est donné par la valeur du sommet à la position i dans la permutation inverse. */
void permutation_inverser(Permutation permutation, Permutation inverse)
{
    assert(permutation != NULL);
    assert(inverse != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    size_t *sommets = permutation->sommets;

    assert(nombre_sommets == inverse->nombre_sommets);

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        size_t sommet = sommets[i];
        inverse->sommets[sommet] = i;
    }
}

size_t size_t_plus_grand_commun_diviseur(size_t a, size_t b)
{
    size_t temp;

    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }

    return a;
}

void permutation_decaler(Permutation permutation, size_t nombre_decalage_gauche)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    nombre_decalage_gauche = nombre_decalage_gauche % nombre_sommets;

    size_t pgcd = size_t_plus_grand_commun_diviseur(nombre_sommets, nombre_decalage_gauche);

    /* Algorithme de décalage du « jongleur ». */
    for (size_t debut_cycle = 0; debut_cycle < pgcd; debut_cycle++)
    {
        size_t sommet = debut_cycle;
        size_t suivant;

        while (true)
        {
            suivant = (sommet + nombre_decalage_gauche) % nombre_sommets;
            if (suivant == debut_cycle)
            {
                break;
            }
            permutation_echanger_sommets(permutation, sommet, suivant);
            sommet = suivant;
        }
    }
}

void permutation_copier(Permutation destination, Permutation source)
{
    assert(destination != NULL);
    assert(source != NULL);

    size_t nombre_sommets = destination->nombre_sommets;

    assert(nombre_sommets == source->nombre_sommets);

    size_t *sommets_destination = destination->sommets;
    size_t *sommets_source = source->sommets;

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        sommets_destination[i] = sommets_source[i];
    }

    size_t taille_distance = destination->taille_distance;

    assert(taille_distance == source->taille_distance);

    memcpy(destination->longueur, source->longueur, taille_distance);
}

size_t permutation_obtenir_nombre_sommets(Permutation permutation)
{
    assert(permutation != NULL);

    return permutation->nombre_sommets;
}

size_t permutation_obtenir_sommet(Permutation permutation, size_t indice)
{
    assert(permutation != NULL);

    return permutation->sommets[indice];
}

void permutation_echanger_sommets(Permutation permutation, size_t sommet_A, size_t sommet_B)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;

    assert(sommet_A < nombre_sommets);
    assert(sommet_B < nombre_sommets);

    size_t *sommets = permutation->sommets;

    size_t_echanger(&sommets[sommet_A], &sommets[sommet_B]);
}

size_t permutation_obtenir_taille_distance(Permutation permutation)
{
    assert(permutation != NULL);

    return permutation->taille_distance;
}

void permutation_obtenir_longueur(Permutation permutation, void *longueur_destination)
{
    assert(permutation != NULL);

    size_t taille_distance = permutation->taille_distance;

    memcpy(longueur_destination, permutation->longueur, taille_distance);
}

void permutation_modifier_longueur(Permutation permutation, void *longueur_source)
{
    assert(permutation != NULL);

    size_t taille_distance = permutation->taille_distance;

    memcpy(permutation->longueur, longueur_source, taille_distance);
}

void permutation_calculer_longueur(
    Permutation permutation, MatriceDistance matrice, DistanceAdditionner distance_additionner)
{
    assert(permutation != NULL);
    assert(matrice != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    size_t *sommets = permutation->sommets;

    TableauDistance tableau_distance = matrice->tableau_distance;
    size_t taille_distance = tableau_distance->taille_distance;
    char *distances = tableau_distance->distances;

    matrice_obtenir_distance(matrice, sommets[0], sommets[nombre_sommets - 1], permutation->longueur);

    for (size_t i = 0; i < nombre_sommets - 1; i++)
    {
        size_t indice = matrice_calculer_indice(sommets[i], sommets[i + 1]);

        distance_additionner(
            permutation->longueur,
            distances + indice * taille_distance,
            permutation->longueur);
    }
}

void permutation_calculer_longueur_avec_elagage(
    Permutation permutation, MatriceDistance matrice,
    void *longueur_destination, void *longueur_minimale,
    DistanceAdditionner distance_additionner, DistanceComparer distance_comparer)
{
    assert(permutation != NULL);
    assert(matrice != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    size_t *sommets = permutation->sommets;

    TableauDistance tableau_distance = matrice->tableau_distance;
    size_t taille_distance = tableau_distance->taille_distance;
    char *distances = tableau_distance->distances;

    matrice_obtenir_distance(matrice, sommets[0], sommets[nombre_sommets - 1], permutation->longueur);

    for (size_t i = 0; i < nombre_sommets - 1; i++)
    {
        if (distance_comparer(permutation->longueur, longueur_minimale) > 0)
        {
            break;
        }

        size_t indice = matrice_calculer_indice(sommets[i], sommets[i + 1]);

        distance_additionner(
            permutation->longueur,
            distances + indice * taille_distance,
            permutation->longueur);
    }
}

bool permutation_avancer(Permutation permutation)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    size_t *sommets = permutation->sommets;

    assert(nombre_sommets != 0);

    size_t pivot = nombre_sommets - 1;

    /* On cherche le plus petit sommet, tel que ceux d'après
     * déterminent une séquence strictement décroissante.
     * Cette séquence s'appelle le suffixe. */
    while (pivot > 1 && sommets[pivot - 1] >= sommets[pivot])
    {
        pivot--;
    }

    /* Si ce plus petit sommet est 1,
     * alors le tableau après le premier sommet est totalement décroissant.
     * On a donc atteint la dernière permutation. */
    if (pivot <= 1)
    {
        return false;
    }

    /* On cherche le sommet le plus petit du suffixe
     * qui est plus grand que le pivot. */
    size_t successeur = nombre_sommets - 1;
    while (sommets[successeur] <= sommets[pivot - 1])
    {
        successeur--;
    }

    permutation_echanger_sommets(permutation, pivot - 1, successeur);

    /* On renverse le suffixe. */
    successeur = nombre_sommets - 1;
    while (pivot < successeur)
    {
        permutation_echanger_sommets(permutation, pivot, successeur);
        pivot++;
        successeur--;
    }

    return true;
}

bool permutation_avancer_et_incrementer_longueur(
    Permutation permutation, MatriceDistance matrice, void *longueur_destination,
    DistanceAdditionner distance_additionner, DistanceSoustraire distance_soustraire)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    size_t *sommets = permutation->sommets;

    assert(nombre_sommets != 0);

    size_t pivot = nombre_sommets - 1;

    /* On cherche le plus petit sommet, tel que ceux d'après
     * déterminent une séquence strictement décroissante.
     * Cette séquence s'appelle le suffixe. */
    while (pivot > 1 && sommets[pivot - 1] >= sommets[pivot])
    {
        pivot--;
    }

    /* Si ce plus petit sommet est 1,
     * alors le tableau après le premier sommet est totalement décroissant.
     * On a donc atteint la dernière permutation. */
    if (pivot <= 1)
    {
        return false;
    }

    /* On cherche le sommet le plus petit du suffixe
     * qui est plus grand que le pivot. */
    size_t successeur = nombre_sommets - 1;
    while (sommets[successeur] <= sommets[pivot - 1])
    {
        successeur--;
    }

    TableauDistance tableau_distance = matrice->tableau_distance;
    size_t taille_distance = tableau_distance->taille_distance;
    char *distances = tableau_distance->distances;

    size_t indice;

    indice = matrice_calculer_indice(sommets[pivot - 2], sommets[pivot - 1]);
    distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[pivot - 1], sommets[pivot]);
    distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);

    if (successeur != pivot)
    {
        indice = matrice_calculer_indice(sommets[successeur - 1], sommets[successeur]);
        distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);
    }

    if (successeur != nombre_sommets - 1)
    {
        indice = matrice_calculer_indice(sommets[successeur], sommets[successeur + 1]);
        distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);
    }

    indice = matrice_calculer_indice(sommets[0], sommets[nombre_sommets - 1]);
    distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);

    permutation_echanger_sommets(permutation, pivot - 1, successeur);

    /* On renverse le suffixe. */
    size_t inf_suffixe = pivot;
    size_t sup_suffixe = nombre_sommets - 1;
    while (inf_suffixe < sup_suffixe)
    {
        permutation_echanger_sommets(permutation, inf_suffixe, sup_suffixe);
        inf_suffixe++;
        sup_suffixe--;
    }

    successeur = nombre_sommets - successeur + pivot - 1;

    indice = matrice_calculer_indice(sommets[pivot - 2], sommets[pivot - 1]);
    distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[pivot - 1], sommets[pivot]);
    distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);

    if (successeur != pivot)
    {
        indice = matrice_calculer_indice(sommets[successeur - 1], sommets[successeur]);
        distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);
    }

    if (successeur != nombre_sommets - 1)
    {
        indice = matrice_calculer_indice(sommets[successeur], sommets[successeur + 1]);
        distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);
    }

    indice = matrice_calculer_indice(sommets[0], sommets[nombre_sommets - 1]);
    distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);

    return true;
}

void permutation_echanger_aretes(Permutation permutation, size_t sommet_A, size_t sommet_B)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;

    assert(sommet_A < nombre_sommets);
    assert(sommet_B < nombre_sommets);

    if (sommet_A > sommet_B)
    {
        size_t_echanger(&sommet_A, &sommet_B);
    }

    sommet_A++;

    while (sommet_A < sommet_B)
    {
        permutation_echanger_sommets(permutation, sommet_A, sommet_B);
        sommet_A++;
        sommet_B--;
    }
}

void permutation_calculer_difference_apres_decroisement(
    MatriceDistance matrice, Permutation permutation,
    size_t sommet_A, size_t sommet_B, void *longueur_destination,
    DistanceAdditionner distance_additionner, DistanceSoustraire distance_soustraire)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation->nombre_sommets;
    size_t *sommets = permutation->sommets;

    assert(sommet_A < nombre_sommets);
    assert(sommet_B < nombre_sommets);

    if (sommet_A > sommet_B)
    {
        size_t_echanger(&sommet_A, &sommet_B);
    }

    size_t suivant_sommet_A = sommet_A + 1;
    size_t suivant_sommet_B = sommet_B + 1;

    if (suivant_sommet_B >= nombre_sommets)
    {
        suivant_sommet_B = 0;
    }

    assert(suivant_sommet_A < nombre_sommets);
    assert(suivant_sommet_B < nombre_sommets);

    TableauDistance tableau_distance = matrice->tableau_distance;
    size_t taille_distance = tableau_distance->taille_distance;
    char *distances = tableau_distance->distances;

    size_t indice;

    indice = matrice_calculer_indice(sommets[sommet_A], sommets[suivant_sommet_A]);
    distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[sommet_B], sommets[suivant_sommet_B]);
    distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[sommet_A], sommets[sommet_B]);
    distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[suivant_sommet_A], sommets[suivant_sommet_B]);
    distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);
}

/*
 * Tableau de permutation.
 */

struct tableau_permutation
{
    size_t nombre_permutations;
    struct permutation *permutations;
};

TableauPermutation tableau_permutation_creer(size_t nombre_permutations, size_t nombre_sommets, size_t taille_distance)
{
    TableauPermutation tableau = malloc(
        sizeof(struct tableau_permutation) +
        nombre_permutations * sizeof(struct permutation));

    if (tableau == NULL)
    {
        fprintf(
            stderr,
            "Erreur tableau_permutation_creer :\n"
            "Échec de l'allocation mémoire de la permutation.\n");
        exit(EXIT_FAILURE);
    }

    tableau->nombre_permutations = nombre_permutations;
    tableau->permutations = (Permutation *)(tableau + 1);

    return tableau;
}

void tableau_permutation_supprimer(TableauPermutation *tableau)
{
    assert(tableau != NULL);
    assert(*tableau != NULL);

    free(*tableau);
    *tableau = NULL;
}

size_t tableau_permutation_obtenir_nombre_permutations(TableauPermutation tableau)
{
    assert(tableau != NULL);

    return tableau->nombre_permutations;
}

Permutation tableau_permutation_obtenir_permutation(TableauPermutation tableau, size_t indice)
{
    assert(tableau != NULL);
    assert(indice < tableau->nombre_permutations);

    return &tableau->permutations[indice];
}

size_t tableau_permutation_trouver_pire_individu(TableauPermutation tableau, DistanceComparer distance_comparer)
{
    assert(tableau != NULL);

    size_t nombre_permutations = tableau->nombre_permutations;

    size_t indice_pire_individu = 0;
    char *longueur_pire_individu = tableau->permutations[indice_pire_individu].longueur;

    for (size_t i = 0; i < nombre_permutations; i++)
    {
        char *longueur = tableau->permutations[i].longueur;

        if (distance_comparer(longueur, longueur_pire_individu) > 0)
        {
            indice_pire_individu = i;
            longueur_pire_individu = tableau->permutations[indice_pire_individu].longueur;
        }
    }

    return indice_pire_individu;
}

size_t tableau_permutation_trouver_meilleur_individu(TableauPermutation tableau, DistanceComparer distance_comparer)
{
    assert(tableau != NULL);

    size_t nombre_permutations = tableau_permutation_obtenir_nombre_permutations(tableau);

    size_t indice_meilleur_individu = 0;
    char *longueur_meilleur_individu = tableau->permutations[indice_meilleur_individu].longueur;

    for (size_t i = 0; i < nombre_permutations; i++)
    {
        char *longueur = tableau->permutations[i].longueur;

        if (distance_comparer(longueur, longueur_meilleur_individu) < 0)
        {
            indice_meilleur_individu = i;
            longueur_meilleur_individu = tableau->permutations[indice_meilleur_individu].longueur;
        }
    }

    return indice_meilleur_individu;
}

void tableau_permutation_echanger_tableaux(TableauPermutation *tableau_A, TableauPermutation *tableau_B)
{
    assert(tableau_A != NULL);
    assert(*tableau_A != NULL);
    assert(tableau_B != NULL);
    assert(*tableau_B != NULL);

    TableauPermutation temp = *tableau_A;
    *tableau_A = *tableau_B;
    *tableau_B = temp;
}

int tableau_permutation_comparer(const void *A, const void *B, void *comparer)
{
    struct permutation permutation_A = *(struct permutation *)A;
    struct permutation permutation_B = *(struct permutation *)B;
    DistanceComparer distance_comparer = (DistanceComparer)comparer;

    return distance_comparer(permutation_A.longueur, permutation_B.longueur);
}

void tableau_permutation_trier(TableauPermutation tableau, DistanceComparer distance_comparer)
{
    assert(tableau != NULL);

    size_t nombre_permutations = tableau->nombre_permutations;

    qsort_r(
        tableau->permutations, nombre_permutations, sizeof(struct permutation),
        tableau_permutation_comparer, distance_comparer);
}
