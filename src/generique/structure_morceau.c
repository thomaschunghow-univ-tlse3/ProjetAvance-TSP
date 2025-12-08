/*
 * structure_morceau.c
 */

#include "structure_morceau.h"

#include "structure_matrice.h"
#include "structure_permutation.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DEBUG */
#include "affichage.h"

struct morceau
{
    size_t nombre_sommets;

    size_t sommet_gauche;
    size_t sommet_droit;
};

struct tableau_morceau
{
    size_t nombre_morceaux;

    struct morceau *morceaux;
};

TableauMorceau tableau_morceau_creer(size_t nombre_morceaux)
{
    TableauMorceau tableau = malloc(sizeof(struct tableau_morceau) + nombre_morceaux * sizeof(struct morceau));

    if (tableau == NULL)
    {
        fprintf(stderr, "Erreur tableau_point_creer :\n"
                        "Échec de l'allocation mémoire du tableau.\n");
        exit(EXIT_FAILURE);
    }

    tableau->nombre_morceaux = nombre_morceaux;

    tableau->morceaux = (struct morceau *)(tableau + 1);

    return tableau;
}

void tableau_morceau_supprimer(TableauMorceau *tableau)
{
    assert(tableau != NULL);
    assert(*tableau != NULL);

    free(*tableau);
    *tableau = NULL;
}

size_t tableau_morceau_obtenir_nombre_morceaux(TableauMorceau tableau)
{
    assert(tableau != NULL);

    return tableau->nombre_morceaux;
}

size_t tableau_morceau_obtenir_nombre_sommets(TableauMorceau tableau, size_t indice)
{
    assert(tableau != NULL);
    assert(indice < tableau_morceau_obtenir_nombre_morceaux(tableau));

    return tableau->morceaux[indice].nombre_sommets;
}

size_t tableau_morceau_obtenir_sommet_gauche(TableauMorceau tableau, size_t indice)
{
    assert(tableau != NULL);
    assert(indice < tableau_morceau_obtenir_nombre_morceaux(tableau));

    return tableau->morceaux[indice].sommet_gauche;
}

size_t tableau_morceau_obtenir_sommet_droit(TableauMorceau tableau, size_t indice)
{
    assert(tableau != NULL);
    assert(indice < tableau_morceau_obtenir_nombre_morceaux(tableau));

    return tableau->morceaux[indice].sommet_droit;
}

void tableau_morceau_modifier_nombre_morceaux(TableauMorceau tableau, size_t nombre_morceaux)
{
    assert(tableau != NULL);

    tableau->nombre_morceaux = nombre_morceaux;
}

void tableau_morceau_modifier_nombre_sommets(TableauMorceau tableau, size_t indice, size_t nombre_sommets)
{
    assert(tableau != NULL);

    tableau->morceaux[indice].nombre_sommets = nombre_sommets;
}

void tableau_morceau_modifier_sommet_gauche(TableauMorceau tableau, size_t indice, size_t sommet_gauche)
{
    assert(tableau != NULL);
    assert(indice < tableau_morceau_obtenir_nombre_morceaux(tableau));

    tableau->morceaux[indice].sommet_gauche = sommet_gauche;
}

void tableau_morceau_modifier_sommet_droit(TableauMorceau tableau, size_t indice, size_t sommet_droit)
{
    assert(tableau != NULL);
    assert(indice < tableau_morceau_obtenir_nombre_morceaux(tableau));

    tableau->morceaux[indice].sommet_droit = sommet_droit;
}

void tableau_morceau_modifier_morceau(TableauMorceau tableau, size_t indice, size_t nombre_sommets,
                                      size_t sommet_gauche, size_t sommet_droit)
{
    assert(tableau != NULL);
    assert(indice < tableau_morceau_obtenir_nombre_morceaux(tableau));

    tableau_morceau_modifier_nombre_sommets(tableau, indice, nombre_sommets);
    tableau_morceau_modifier_sommet_gauche(tableau, indice, sommet_gauche);
    tableau_morceau_modifier_sommet_droit(tableau, indice, sommet_droit);
}

void tableau_morceau_echanger_sommets_gauche_et_droit(TableauMorceau tableau, size_t indice)
{
    assert(tableau != NULL);
    assert(indice < tableau_morceau_obtenir_nombre_morceaux(tableau));

    size_t_echanger(&tableau->morceaux[indice].sommet_gauche, &tableau->morceaux[indice].sommet_droit);
}

void tableau_morceau_echanger_morceaux(TableauMorceau tableau, size_t indice_A, size_t indice_B)
{
    assert(tableau != NULL);
    assert(indice_A < tableau_morceau_obtenir_nombre_morceaux(tableau));
    assert(indice_B < tableau_morceau_obtenir_nombre_morceaux(tableau));

    struct morceau temp = tableau->morceaux[indice_A];
    tableau->morceaux[indice_A] = tableau->morceaux[indice_B];
    tableau->morceaux[indice_B] = temp;
}

/* Décalage des morceaux entre les sommets A et B (inclus). */
void tableau_morceau_decaler_morceau(TableauMorceau tableau, size_t nombre_decalage_gauche, size_t sommet_A,
                                     size_t sommet_B)
{
    if (sommet_A > sommet_B)
    {
        size_t_echanger(&sommet_A, &sommet_B);
    }

    size_t nombre_sommets = sommet_B - sommet_A + 1;
    nombre_decalage_gauche = nombre_decalage_gauche % nombre_sommets;

    size_t pgcd = size_t_plus_grand_commun_diviseur(nombre_sommets, nombre_decalage_gauche);

    /* Algorithme de décalage du « jongleur ». */
    for (size_t debut_cycle = 0; debut_cycle < pgcd; debut_cycle++)
    {
        size_t sommet = debut_cycle + sommet_A;
        size_t suivant;

        while (true)
        {
            suivant = sommet_A + (sommet + nombre_sommets - sommet_A + nombre_decalage_gauche) % (nombre_sommets);

            if (suivant == debut_cycle + sommet_A)
            {
                break;
            }

            tableau_morceau_echanger_morceaux(tableau, sommet, suivant);

            sommet = suivant;
        }
    }
}

void tableau_morceau_decaler_sommets_morceau(TableauMorceau morceaux, size_t indice_morceau_A, size_t indice_morceau_B,
                                             size_t nombre_decalage_gauche, size_t sommet_A, size_t sommet_B)
{
    if (sommet_A > sommet_B)
    {
        size_t_echanger(&sommet_A, &sommet_B);
    }

    if (indice_morceau_A > indice_morceau_B)
    {
        size_t_echanger(&indice_morceau_A, &indice_morceau_B);
    }

    for (size_t i = indice_morceau_A; i <= indice_morceau_B; i++)
    {
        size_t nombre_sommets = sommet_B - sommet_A + 1;
        nombre_decalage_gauche = nombre_decalage_gauche % nombre_sommets;

        size_t morceau_sommet_gauche = tableau_morceau_obtenir_sommet_gauche(morceaux, i);
        size_t morceau_sommet_droit = tableau_morceau_obtenir_sommet_droit(morceaux, i);

        printf("Pour indice = %lu\n", i);
        morceau_sommet_gauche =
            sommet_A + (morceau_sommet_gauche - sommet_A - nombre_decalage_gauche) % (nombre_sommets);
        morceau_sommet_droit = sommet_A + (morceau_sommet_droit - sommet_A - nombre_decalage_gauche) % (nombre_sommets);

        tableau_morceau_modifier_sommet_gauche(morceaux, i, morceau_sommet_gauche);
        tableau_morceau_modifier_sommet_droit(morceaux, i, morceau_sommet_droit);

        afficher_morceaux(stdout, morceaux);
    }
}
