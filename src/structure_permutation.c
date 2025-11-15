/*
 * structure_permutation.c
 */

#include "structure_permutation.h"
#include "traitement_tournee.h"
#include "affichage.h" // DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct permutation
{
    size_t nombre_sommets;
    size_t *sommets;
};

void permutation_initialiser(Permutation permutation)
{
    for (size_t i = 0; i < permutation_obtenir_taille(permutation); i++)
    {
        permutation->sommets[i] = i;
    }
}

Permutation permutation_creer(size_t nombre_sommets)
{
    Permutation permutation = malloc(sizeof(struct permutation) +
                                     nombre_sommets * sizeof(size_t));

    if (permutation == NULL)
    {
        fprintf(stderr,
                "Erreur permutation_creer :\n"
                "Echec de l'allocation mémoire de la permutation.\n");
        exit(EXIT_FAILURE);
    }

    permutation->nombre_sommets = nombre_sommets;
    permutation->sommets = (size_t *)(permutation + 1);

    permutation_initialiser(permutation);

    return permutation;
}

void permutation_assert_non_vide(Permutation permutation)
{
    assert(permutation != NULL);
    (void)permutation;
}

void permutation_assert_indice_valide(Permutation permutation, size_t indice)
{
    assert(indice < permutation_obtenir_taille(permutation));
    (void)permutation;
    (void)indice;
}

void permutation_supprimer(Permutation *permutation)
{
    permutation_assert_non_vide(*permutation);

    free(*permutation);
    *permutation = NULL;
}

size_t permutation_obtenir_taille(Permutation permutation)
{
    permutation_assert_non_vide(permutation);

    return permutation->nombre_sommets;
}

size_t permutation_obtenir_sommet(Permutation permutation, size_t indice)
{
    permutation_assert_non_vide(permutation);

    return permutation->sommets[indice];
}

void permutation_echanger_sommets(Permutation permutation, size_t sommet_A, size_t sommet_B)
{
    permutation_assert_non_vide(permutation);

    permutation_assert_indice_valide(permutation, sommet_A);
    permutation_assert_indice_valide(permutation, sommet_B);

    size_t *sommets = permutation->sommets;

    size_t temp = sommets[sommet_A];
    sommets[sommet_A] = sommets[sommet_B];
    sommets[sommet_B] = temp;
}

distance permutation_calculer_distance_totale(Permutation permutation, MatriceDistance matrice)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    const size_t *sommets = permutation->sommets;

    distance longueur = matrice_obtenir_distance(matrice, sommets[0], sommets[nombre_sommets - 1]);
    for (size_t i = 0; i < nombre_sommets - 1; i++)
    {
        longueur += matrice_obtenir_distance(matrice, sommets[i], sommets[i + 1]);
    }

    return longueur;
}

distance permutation_calculer_distance_totale_avec_elagage(Permutation permutation, MatriceDistance matrice, distance longueur_minimale)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    const size_t *sommets = permutation->sommets;

    distance longueur = matrice_obtenir_distance(matrice, sommets[0], sommets[nombre_sommets - 1]);
    for (size_t i = 0; i < nombre_sommets - 1; i++)
    {
        if (longueur > longueur_minimale)
        {
            break;
        }

        longueur += matrice_obtenir_distance(matrice, sommets[i], sommets[i + 1]);
    }

    return longueur;
}

void permutation_copier(Permutation destination, Permutation source)
{
    for (size_t i = 0; i < permutation_obtenir_taille(destination); i++)
    {
        destination->sommets[i] = source->sommets[i];
    }
}

bool permutation_avancer(Permutation permutation)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    const size_t *sommets = permutation->sommets;

    if (nombre_sommets == 0)
    {
        return false;
    }

    size_t pivot = nombre_sommets - 1;

    /* On cherche le plus petit sommet, tel que ceux d'après déterminent une séquence strictement décroissante.
     * Cette séquence s'appelle le suffixe. */
    while (pivot > 1 && sommets[pivot - 1] >= sommets[pivot])
    {
        pivot--;
    }

    /* Si ce plus petit sommet est 1, alors le tableau après le premier sommet est totalement décroissant.
     * On a donc atteint la dernière permutation. */
    if (pivot <= 1)
    {
        return false;
    }

    /* On cherche le sommet le plus petit du suffixe qui est plus grand que le pivot. */
    size_t successeur = nombre_sommets - 1;
    while (sommets[successeur] <= sommets[pivot - 1])
    {
        successeur--;
    }

    permutation_echanger_sommets(permutation, pivot - 1, successeur);

    /* On inverse le suffixe. */
    successeur = nombre_sommets - 1;
    while (pivot < successeur)
    {
        permutation_echanger_sommets(permutation, pivot, successeur);
        pivot++;
        successeur--;
    }

    return true;
}

bool permutation_avancer_et_incrementer_longueur(Permutation permutation, MatriceDistance matrice, distance *longueur)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    const size_t *sommets = permutation->sommets;

    if (nombre_sommets == 0)
    {
        return false;
    }

    size_t pivot = nombre_sommets - 1;

    /* On cherche le plus petit sommet, tel que ceux d'après déterminent une séquence strictement décroissante.
     * Cette séquence s'appelle le suffixe. */
    while (pivot > 1 && sommets[pivot - 1] >= sommets[pivot])
    {
        pivot--;
    }

    /* Si ce plus petit sommet est 1, alors le tableau après le premier sommet est totalement décroissant.
     * On a donc atteint la dernière permutation. */
    if (pivot <= 1)
    {
        return false;
    }

    /* On cherche le sommet le plus petit du suffixe qui est plus grand que le pivot. */
    size_t successeur = nombre_sommets - 1;
    while (sommets[successeur] <= sommets[pivot - 1])
    {
        successeur--;
    }

    *longueur -= matrice_obtenir_distance(matrice, sommets[pivot - 2], sommets[pivot - 1]);
    *longueur -= matrice_obtenir_distance(matrice, sommets[pivot - 1], sommets[pivot]);
    if (successeur != pivot)
    {
        *longueur -= matrice_obtenir_distance(matrice, sommets[successeur - 1], sommets[successeur]);
    }
    if (successeur != nombre_sommets - 1)
    {
        *longueur -= matrice_obtenir_distance(matrice, sommets[successeur], sommets[successeur + 1]);
    }
    *longueur -= matrice_obtenir_distance(matrice, sommets[0], sommets[nombre_sommets - 1]);

    permutation_echanger_sommets(permutation, pivot - 1, successeur);

    /* On inverse le suffixe. */
    size_t inf_suffixe = pivot;
    size_t sup_suffixe = nombre_sommets - 1;
    while (inf_suffixe < sup_suffixe)
    {
        permutation_echanger_sommets(permutation, inf_suffixe, sup_suffixe);
        inf_suffixe++;
        sup_suffixe--;
    }

    successeur = nombre_sommets - successeur + pivot - 1;

    *longueur += matrice_obtenir_distance(matrice, sommets[pivot - 2], sommets[pivot - 1]);
    *longueur += matrice_obtenir_distance(matrice, sommets[pivot - 1], sommets[pivot]);
    if (successeur != pivot)
    {
        *longueur += matrice_obtenir_distance(matrice, sommets[successeur - 1], sommets[successeur]);
    }
    if (successeur != nombre_sommets - 1)
    {
        *longueur += matrice_obtenir_distance(matrice, sommets[successeur], sommets[successeur + 1]);
    }
    *longueur += matrice_obtenir_distance(matrice, sommets[0], sommets[nombre_sommets - 1]);

    return true;
}

void permutation_echanger_aretes(Permutation permutation, size_t sommet_A, size_t sommet_B)
{
    permutation_assert_non_vide(permutation);

    permutation_assert_indice_valide(permutation, sommet_A);
    permutation_assert_indice_valide(permutation, sommet_B);

    if (sommet_A > sommet_B)
    {
        echanger(&sommet_A, &sommet_B);
    }

    sommet_A++;

    while (sommet_A < sommet_B)
    {
        permutation_echanger_sommets(permutation, sommet_A, sommet_B);
        sommet_A++;
        sommet_B--;
    }
}

distance permutation_difference_apres_decroisement(MatriceDistance matrice, Permutation permutation, size_t sommet_A, size_t sommet_B)
{
    permutation_assert_non_vide(permutation);

    permutation_assert_indice_valide(permutation, sommet_A);
    permutation_assert_indice_valide(permutation, sommet_B);

    if (sommet_A > sommet_B)
    {
        echanger(&sommet_A, &sommet_B);
    }

    size_t suivant_sommet_A = sommet_A + 1;
    size_t suivant_sommet_B = sommet_B + 1;

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    if (suivant_sommet_B >= nombre_sommets)
    {
        suivant_sommet_B = 0;
    }

    permutation_assert_indice_valide(permutation, suivant_sommet_A);
    permutation_assert_indice_valide(permutation, suivant_sommet_B);

    distance difference = 0;

    difference -= matrice_obtenir_distance(matrice, permutation_obtenir_sommet(permutation, sommet_A), permutation_obtenir_sommet(permutation, suivant_sommet_A));
    difference -= matrice_obtenir_distance(matrice, permutation_obtenir_sommet(permutation, sommet_B), permutation_obtenir_sommet(permutation, suivant_sommet_B));

    difference += matrice_obtenir_distance(matrice, permutation_obtenir_sommet(permutation, sommet_A), permutation_obtenir_sommet(permutation, sommet_B));
    difference += matrice_obtenir_distance(matrice, permutation_obtenir_sommet(permutation, suivant_sommet_A), permutation_obtenir_sommet(permutation, suivant_sommet_B));

    return difference;
}

size_t permutation_obtenir_indice_sommet(Permutation permutation, size_t sommet_cherche)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        if (permutation_obtenir_sommet(permutation, i) == sommet_cherche)
        {
            return i;
        }
    }

    fprintf(stderr,
            "Erreur permutation_obtenir_indice_sommet :\n"
            "Sommet absent de la permutation.\n");
    exit(EXIT_FAILURE);
}

void permutation_decaler(Permutation permutation, size_t nombre_decalage_gauche)
{
    permutation_assert_non_vide(permutation);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    nombre_decalage_gauche = nombre_decalage_gauche % nombre_sommets;

    for (size_t rotation = 0; rotation < nombre_decalage_gauche; rotation++)
    {
        for (size_t i = 0; i < nombre_sommets - 1; i++)
        {
            size_t indice_a_echanger = (i + 1) % nombre_sommets;
            permutation_echanger_sommets(permutation, i, indice_a_echanger);
        }
    }
}

void permutation_croisement_ordonne(Permutation pere, Permutation mere, Permutation enfant, size_t sommet_A, size_t sommet_B)
{
    permutation_assert_non_vide(pere);
    permutation_assert_non_vide(mere);
    permutation_assert_non_vide(enfant);

    permutation_assert_indice_valide(pere, sommet_A);
    permutation_assert_indice_valide(pere, sommet_B);
    permutation_assert_indice_valide(mere, sommet_A);
    permutation_assert_indice_valide(mere, sommet_B);
    permutation_assert_indice_valide(enfant, sommet_A);
    permutation_assert_indice_valide(enfant, sommet_B);

    size_t nombre_sommets = permutation_obtenir_taille(pere);

    if (sommet_B < sommet_A)
    {
        echanger(&sommet_A, &sommet_B);
    }
    size_t nombre_sommets_pere_herite = sommet_B + 1 - sommet_A;

    /* Le segment copié du père est placé au début de l'enfant. */
    permutation_copier(enfant, pere);
    permutation_decaler(enfant, sommet_A);

    /* On remplit le reste de l'enfant avec les sommets restants dans l'ordre de la mère. */
    size_t indice_enfant = nombre_sommets_pere_herite;
    for (size_t indice_mere = 0; indice_mere < nombre_sommets; indice_mere++)
    {
        // assert(indice_enfant < nombre_sommets);

        size_t sommet_mere = permutation_obtenir_sommet(mere, indice_mere);
        size_t indice_sommet_a_echanger = permutation_obtenir_indice_sommet(enfant, sommet_mere);

        if (indice_sommet_a_echanger >= nombre_sommets_pere_herite)
        {
            permutation_echanger_sommets(enfant, indice_sommet_a_echanger, indice_enfant);
            indice_enfant++;
        }
    }
}

struct tableau_permutation
{
    size_t nombre_permutations;
    Resultat *resultats;
};

void tableau_permutation_assert_non_vide(TableauPermutation permutations)
{
    assert(permutations != NULL);
    (void)permutations;
}

void tableau_permutation_assert_indice_valide(TableauPermutation permutations, size_t indice)
{
    assert(indice < permutations->nombre_permutations);
    (void)permutations;
    (void)indice;
}

TableauPermutation tableau_permutation_creer(size_t nombre_permutations)
{
    TableauPermutation permutations = malloc(sizeof(struct tableau_permutation) +
                                             nombre_permutations * sizeof(Resultat));

    if (permutations == NULL)
    {
        fprintf(stderr,
                "Erreur tableau_permutation_creer :\n"
                "Echec de l'allocation mémoire de la permutation.\n");
        exit(EXIT_FAILURE);
    }

    permutations->nombre_permutations = nombre_permutations;
    permutations->resultats = (Resultat *)(permutations + 1);

    for (size_t i = 0; i < nombre_permutations; i++)
    {
        permutations->resultats[i].permutation = NULL;
        permutations->resultats[i].longueur = 0;
    }

    return permutations;
}

void tableau_permutation_vider_sauf_une(TableauPermutation permutations, size_t permutation_a_conserver)
{
    tableau_permutation_assert_non_vide(permutations);

    for (size_t i = 0; i < permutations->nombre_permutations; i++)
    {
        if (i != permutation_a_conserver)
        {
            permutation_assert_non_vide(permutations->resultats[i].permutation);

            permutation_supprimer(&(permutations->resultats[i].permutation));
        }
    }
}

void tableau_permutation_supprimer(TableauPermutation *permutations)
{
    tableau_permutation_assert_non_vide(*permutations);

    free(*permutations);
    *permutations = NULL;
}

size_t tableau_permutation_obtenir_nombre_permutation(TableauPermutation tableau)
{
    tableau_permutation_assert_non_vide(tableau);

    return tableau->nombre_permutations;
}

Permutation tableau_permutation_obtenir_permutation(TableauPermutation tableau, size_t indice)
{
    tableau_permutation_assert_non_vide(tableau);

    tableau_permutation_assert_indice_valide(tableau, indice);

    return tableau->resultats[indice].permutation;
}

void tableau_permutation_modifier_permutation(TableauPermutation tableau, size_t indice, Permutation permutation)
{
    tableau_permutation_assert_non_vide(tableau);

    tableau_permutation_assert_indice_valide(tableau, indice);

    tableau->resultats[indice].permutation = permutation;
}

distance tableau_permutation_obtenir_longueur(TableauPermutation tableau, size_t indice)
{
    tableau_permutation_assert_non_vide(tableau);

    tableau_permutation_assert_indice_valide(tableau, indice);

    return tableau->resultats[indice].longueur;
}

void tableau_permutation_modifier_longueur(TableauPermutation tableau, size_t indice, distance longueur)
{
    tableau_permutation_assert_non_vide(tableau);

    tableau_permutation_assert_indice_valide(tableau, indice);

    tableau->resultats[indice].longueur = longueur;
}

size_t tableau_permutation_trouver_pire_individu(TableauPermutation tableau)
{
    size_t nombre_permutations = tableau_permutation_obtenir_nombre_permutation(tableau);

    size_t indice_pire_individu = 0;
    distance longueur_pire_individu = tableau_permutation_obtenir_longueur(tableau, indice_pire_individu);

    for (size_t i = 0; i < nombre_permutations; i++)
    {
        distance longueur = tableau_permutation_obtenir_longueur(tableau, i);

        if (longueur_pire_individu < longueur)
        {
            indice_pire_individu = i;
            longueur_pire_individu = tableau_permutation_obtenir_longueur(tableau, indice_pire_individu);
        }
    }

    return indice_pire_individu;
}

size_t tableau_permutation_trouver_meilleur_individu(TableauPermutation tableau)
{
    size_t nombre_permutations = tableau_permutation_obtenir_nombre_permutation(tableau);

    size_t indice_meilleur_individu = 0;
    distance longueur_meilleur_individu = tableau_permutation_obtenir_longueur(tableau, indice_meilleur_individu);

    for (size_t i = 0; i < nombre_permutations; i++)
    {
        distance longueur = tableau_permutation_obtenir_longueur(tableau, i);

        if (longueur_meilleur_individu > longueur)
        {
            indice_meilleur_individu = i;
            longueur_meilleur_individu = tableau_permutation_obtenir_longueur(tableau, indice_meilleur_individu);
        }
    }

    return indice_meilleur_individu;
}
