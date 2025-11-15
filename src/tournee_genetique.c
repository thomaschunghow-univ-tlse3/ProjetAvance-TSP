/*
 * tournee_genetique.c
 */

#include "tournee_genetique.h"
#include "structure_permutation.h"
#include "structure_matrice.h"
#include "tournee_2_optimisation.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>

void tournee_genetique_mutation(Permutation permutation, double taux_mutation)
{
    size_t nombre_sommets = permutation_obtenir_taille(permutation);

    for (size_t i = 0; i < nombre_sommets; i++)
    {
        double probabilite_mutation = donner_reel_aleatoire(0, 1);

        if (probabilite_mutation < taux_mutation)
        {
            size_t indice_a_echanger = donner_entier_aleatoire(0, nombre_sommets);
            permutation_echanger_sommets(permutation, i, indice_a_echanger);
        }
    }
}

Resultat tournee_genetique_generique(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    TableauPermutation population = tableau_permutation_creer(nombre_individus);
    size_t nombre_sommets = matrice_obtenir_nombre_points(matrice);

    Resultat resultat;

    /* Initialisation de la population initiale. */
    for (size_t i = 0; i < nombre_individus; i++)
    {
        resultat = tournee_marche_aleatoire(matrice);
        tableau_permutation_modifier_permutation(population, i, resultat.permutation);
        tableau_permutation_modifier_longueur(population, i, resultat.longueur);
    }

#ifdef AFFICHAGE_INTERACTIF
    for (size_t individu = 0; individu < nombre_individus; individu++)
    {
        Permutation permutation = tableau_permutation_obtenir_permutation(population, individu);
        afficher_permutation(sortie_interactive, permutation, 0);
        fprintf(sortie_interactive, "\n");
    }
#endif

    Permutation enfant = permutation_creer(nombre_sommets);

    for (size_t generation = 0; generation < nombre_generations; generation++)
    {
        /* Sélection au hasard de deux individus. */
        size_t indice_pere;
        size_t indice_mere;

        indice_pere = donner_entier_aleatoire(0, nombre_individus);
        do
        {
            indice_mere = donner_entier_aleatoire(0, nombre_individus);
        } while (indice_pere == indice_mere);

        Permutation pere = tableau_permutation_obtenir_permutation(population, indice_pere);
        Permutation mere = tableau_permutation_obtenir_permutation(population, indice_mere);

        /* Croisement entre les deux parents. */
        size_t sommet_A = donner_entier_aleatoire(0, nombre_sommets);
        size_t sommet_B = donner_entier_aleatoire(0, nombre_sommets);

        permutation_croisement_ordonne(pere, mere, enfant, sommet_A, sommet_B);

        /* Mutation de l'enfant. */
        tournee_genetique_mutation(enfant, taux_mutation);
        distance longueur_enfant = permutation_calculer_distance_totale(enfant, matrice);

        /* Intégration de la fille dans la population. */
        size_t indice_pire_individu = tableau_permutation_trouver_pire_individu(population);

        Permutation pire_individu = tableau_permutation_obtenir_permutation(population, indice_pire_individu);
        permutation_copier(pire_individu, enfant);
        tableau_permutation_modifier_longueur(population, indice_pire_individu, longueur_enfant);

#ifdef AFFICHAGE_INTERACTIF
        for (size_t individu = 0; individu < nombre_individus; individu++)
        {
            Permutation permutation = tableau_permutation_obtenir_permutation(population, individu);
            afficher_permutation(sortie_interactive, permutation, 0);
            fprintf(sortie_interactive, "\n");
        }
#endif
    }

    permutation_supprimer(&enfant);

    size_t indice_meilleur_individu = tableau_permutation_trouver_meilleur_individu(population);

    resultat.permutation = tableau_permutation_obtenir_permutation(population, indice_meilleur_individu);
    resultat.longueur = tableau_permutation_obtenir_longueur(population, indice_meilleur_individu);

    tableau_permutation_vider_sauf_une(population, indice_meilleur_individu);
    tableau_permutation_supprimer(&population);

    return resultat;
}

Resultat tournee_genetique_dpx(MatriceDistance m, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    return tournee_genetique_generique(m, nombre_individus, nombre_generations, taux_mutation); // A remplacer par une vraie implémentation DPX
}