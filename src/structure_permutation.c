/*
 * structure_permutation.c
 */

#include "structure_permutation.h"
#include "traitement_tournee.h"
#include "nombre_aleatoire.h"

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

void permutation_initialiser_aleatoirement(Permutation permutation)
{
    size_t nombre_sommets = permutation_obtenir_taille(permutation);

    for (size_t sommet = 0; sommet < nombre_sommets - 1; sommet++)
    {
        size_t voisin = donner_entier_aleatoire(sommet, nombre_sommets);

        permutation_echanger_sommets(permutation, sommet, voisin);
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
	if(permutation == NULL)
		printf("permutation nulle\n");
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
    permutation_assert_non_vide(destination);
    permutation_assert_non_vide(source);

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
        matrice_echanger_indices(&sommet_A, &sommet_B);
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
        matrice_echanger_indices(&sommet_A, &sommet_B);
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

/* Inverse au sens mathématique. C'est-à-dire, la position du sommet de valeur i dans la permutation
 * est donné par la valeur du sommet à la position i dans la permutation inverse. */
void permutation_inverser(Permutation permutation, Permutation inverse)
{
    permutation_assert_non_vide(permutation);
    permutation_assert_non_vide(inverse);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    assert(nombre_sommets == permutation_obtenir_taille(inverse));

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        size_t valeur_sommet = permutation_obtenir_sommet(permutation, i);
        inverse->sommets[valeur_sommet] = i;
    }
}

size_t plus_grand_commun_diviseur(size_t a, size_t b)
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
    permutation_assert_non_vide(permutation);

    size_t nombre_sommets = permutation_obtenir_taille(permutation);
    nombre_decalage_gauche = nombre_decalage_gauche % nombre_sommets;

    size_t pgcd = plus_grand_commun_diviseur(nombre_sommets, nombre_decalage_gauche);

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
