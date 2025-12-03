/*
 * structure_permutation.c
 */

#include "structure_permutation.h"

#include "structure_matrice_interne.h"
#include "structure_permutation_interne.h"

#include "nombre_aleatoire.h"
#include "structure_matrice.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    permutation->taille_distance = taille_distance;
    permutation->longueur = (char *)(permutation + 1);
    permutation->sommets = (size_t *)(permutation->longueur + taille_distance);

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

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
    size_t *sommets = permutation->sommets;

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        sommets[i] = i;
    }

    size_t taille_distance = permutation_obtenir_taille_distance(permutation);
    memset(permutation->longueur, 0, taille_distance);
}

void permutation_melanger(Permutation permutation)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);

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

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
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

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
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

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(destination);

    assert(nombre_sommets == permutation_obtenir_nombre_sommets(source));

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
    assert(sommet_A < permutation_obtenir_nombre_sommets(permutation));
    assert(sommet_B < permutation_obtenir_nombre_sommets(permutation));

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
    assert(longueur_destination != NULL);

    size_t taille_distance = permutation_obtenir_taille_distance(permutation);

    memcpy(longueur_destination, permutation->longueur, taille_distance);
}

void permutation_modifier_longueur(Permutation permutation, void *longueur_source)
{
    assert(permutation != NULL);

    size_t taille_distance = permutation_obtenir_taille_distance(permutation);

    memcpy(permutation->longueur, longueur_source, taille_distance);
}

int permutation_comparer_longueurs(Permutation permutation_A, Permutation permutation_B, DistanceComparer distance_comparer)
{
    return distance_comparer(permutation_A->longueur, permutation_B->longueur);
}

void permutation_calculer_longueur(
    Permutation permutation, MatriceDistance matrice)
{
    assert(permutation != NULL);
    assert(matrice != NULL);

    DistanceAdditionner distance_additionner = matrice_obtenir_distance_additionner(matrice);
    assert(distance_additionner != NULL);

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
    size_t *sommets = permutation->sommets;

    size_t taille_distance = matrice_obtenir_taille_distance(matrice);

    matrice_obtenir_distance(matrice, sommets[nombre_sommets - 1], sommets[0], permutation->longueur);

    for (size_t i = 0; i < nombre_sommets - 1; i++)
    {
        size_t indice = matrice_calculer_indice(sommets[i + 1], sommets[i]);
        char *distance = matrice->tableau_distance.distances + indice * taille_distance;

        distance_additionner(
            permutation->longueur,
            distance,
            permutation->longueur);
    }
}

void permutation_calculer_longueur_avec_elagage(
    Permutation permutation, MatriceDistance matrice, Permutation permutation_minimale)
{
    assert(permutation != NULL);
    assert(matrice != NULL);

    DistanceAdditionner distance_additionner = matrice_obtenir_distance_additionner(matrice);
    assert(distance_additionner != NULL);

    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);
    assert(distance_comparer != NULL);

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
    size_t *sommets = permutation->sommets;

    size_t taille_distance = matrice_obtenir_taille_distance(matrice);

    matrice_obtenir_distance(matrice, sommets[nombre_sommets - 1], sommets[0], permutation->longueur);

    void *longueur_minimale = permutation_minimale->longueur;

    for (size_t i = 0; i < nombre_sommets - 1; i++)
    {
        if (distance_comparer(permutation->longueur, longueur_minimale) > 0)
        {
            break;
        }

        size_t indice = matrice_calculer_indice(sommets[i + 1], sommets[i]);
        char *distance = matrice->tableau_distance.distances + indice * taille_distance;

        distance_additionner(
            permutation->longueur,
            distance,
            permutation->longueur);
    }
}

bool permutation_avancer(Permutation permutation)
{
    assert(permutation != NULL);

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
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
    Permutation permutation, MatriceDistance matrice)
{
    assert(permutation != NULL);

    DistanceAdditionner distance_additionner = matrice_obtenir_distance_additionner(matrice);
    assert(distance_additionner != NULL);

    DistanceSoustraire distance_soustraire = matrice_obtenir_distance_soustraire(matrice);
    assert(distance_soustraire != NULL);

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
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

    size_t taille_distance = matrice_obtenir_taille_distance(matrice);
    char *distances = matrice->tableau_distance.distances;

    size_t indice;
    void *longueur_destination = permutation->longueur;

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
    assert(sommet_A < permutation_obtenir_nombre_sommets(permutation));
    assert(sommet_B < permutation_obtenir_nombre_sommets(permutation));

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

bool permutation_decroiser(
    MatriceDistance matrice, Permutation permutation,
    size_t sommet_A, size_t sommet_B, Permutation permutation_decroisee)
{
    assert(permutation != NULL);

    DistanceAdditionner distance_additionner = matrice_obtenir_distance_additionner(matrice);
    assert(distance_additionner != NULL);

    DistanceSoustraire distance_soustraire = matrice_obtenir_distance_soustraire(matrice);
    assert(distance_soustraire != NULL);

    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);
    assert(distance_comparer != NULL);

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);
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

    size_t taille_distance = matrice_obtenir_taille_distance(matrice);
    char *distances = matrice->tableau_distance.distances;

    size_t indice;

    char *longueur_destination = permutation_decroisee->longueur;

    indice = matrice_calculer_indice(sommets[sommet_A], sommets[suivant_sommet_A]);
    distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[sommet_B], sommets[suivant_sommet_B]);
    distance_soustraire(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[sommet_A], sommets[sommet_B]);
    distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);

    indice = matrice_calculer_indice(sommets[suivant_sommet_A], sommets[suivant_sommet_B]);
    distance_additionner(longueur_destination, distances + indice * taille_distance, longueur_destination);

    if (permutation_comparer_longueurs(permutation_decroisee, permutation, distance_comparer) < 0)
    {
        permutation_echanger_aretes(permutation, sommet_A, sommet_B);
        permutation_echanger_aretes(permutation_decroisee, sommet_A, sommet_B);
        memcpy(permutation->longueur, permutation_decroisee->longueur, taille_distance);

        return true;
    }

    memcpy(permutation_decroisee->longueur, permutation->longueur, taille_distance);

    return false;
}
