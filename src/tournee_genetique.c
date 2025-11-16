/*
 * tournee_genetique.c
 */

#include "tournee_genetique.h"
#include "structure_permutation.h"
#include "structure_matrice.h"
#include "affichage.h"

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

        if (probabilite_mutation < taux_mutation / 2)
        {
            size_t indice_a_echanger = donner_entier_aleatoire(0, nombre_sommets);
            permutation_echanger_sommets(permutation, i, indice_a_echanger);
        }
    }
}

Resultat tournee_genetique_generique(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    TableauPermutation population = tableau_permutation_creer(nombre_individus);
    TableauPermutation enfants = tableau_permutation_creer(nombre_individus);

    size_t nombre_sommets = matrice_obtenir_nombre_points(matrice);

    /* Allocation mémoire des enfants. */
    for (size_t i = 0; i < nombre_individus; i++)
    {
        Permutation enfant = permutation_creer(nombre_sommets);
        tableau_permutation_modifier_permutation(enfants, i, enfant);
    }

    /* Allocation mémoire et initialisation de la population initiale. */
    for (size_t i = 0; i < nombre_individus; i++)
    {
        Permutation individu = permutation_creer(nombre_sommets);
        permutation_initialiser_aleatoirement(individu);
        tableau_permutation_modifier_permutation(population, i, individu);
        distance longueur = permutation_calculer_distance_totale(individu, matrice);
        tableau_permutation_modifier_longueur(population, i, longueur);
    }

    /* Initialisation du meilleur individu historique,
     * c'est-à-dire du meilleur individu parmi toutes les générations confondues. */
    Permutation meilleur_individu_historique = permutation_creer(nombre_sommets);
    size_t indice_meilleur_individu = tableau_permutation_trouver_meilleur_individu(population);
    Permutation meilleur_individu = tableau_permutation_obtenir_permutation(population, indice_meilleur_individu);
    permutation_copier(meilleur_individu_historique, meilleur_individu);
    distance longueur_meilleur_individu_historique = permutation_calculer_distance_totale(meilleur_individu_historique, matrice);

#ifdef AFFICHAGE_INTERACTIF
    for (size_t individu = 0; individu < nombre_individus; individu++)
    {
        Permutation permutation = tableau_permutation_obtenir_permutation(population, individu);
        afficher_permutation(sortie_interactive, permutation, 0);
        fprintf(sortie_interactive, "\n");
    }
#endif

    for (size_t generation = 0; generation < nombre_generations; generation++)
    {
        for (size_t indice_enfant = 0; indice_enfant < nombre_individus / 2; indice_enfant++)
        {
            /* Remarque : si le nombre d'individus est impair, alors le pire individu ne se reproduit pas. */
            indice_enfant *= 2;
            size_t indice_pere = indice_enfant;
            size_t indice_mere = indice_pere + 1;
            size_t indice_frere = indice_pere;
            size_t indice_soeur = indice_mere;

            /* Sélection de deux individus. */
            Permutation pere = tableau_permutation_obtenir_permutation(population, indice_pere);
            Permutation mere = tableau_permutation_obtenir_permutation(population, indice_mere);

            /* Croisement entre les deux parents. */
            Permutation frere = tableau_permutation_obtenir_permutation(enfants, indice_frere);
            Permutation soeur = tableau_permutation_obtenir_permutation(enfants, indice_soeur);

            size_t sommet_A = donner_entier_aleatoire(0, nombre_sommets);
            size_t sommet_B = donner_entier_aleatoire(0, nombre_sommets);
            permutation_croisement_ordonne(pere, mere, frere, sommet_A, sommet_B);

            sommet_A = donner_entier_aleatoire(0, nombre_sommets);
            sommet_B = donner_entier_aleatoire(0, nombre_sommets);
            permutation_croisement_ordonne(pere, mere, soeur, sommet_A, sommet_B);
        }

        for (size_t indice_enfant = 0; indice_enfant < nombre_individus; indice_enfant++)
        {
            /* Mutation de l'enfant. */
            Permutation enfant = tableau_permutation_obtenir_permutation(enfants, indice_enfant);

            tournee_genetique_mutation(enfant, taux_mutation);

            distance longueur = permutation_calculer_distance_totale(enfant, matrice);
            tableau_permutation_modifier_longueur(enfants, indice_enfant, longueur);
        }

        tableau_permutation_trier(enfants);

        /* Remplacement du pire individu de cette génération par un nouvel individu. */
        size_t indice_pire_individu = tableau_permutation_trouver_pire_individu(enfants);
        Permutation pire_individu = tableau_permutation_obtenir_permutation(enfants, indice_pire_individu);
        permutation_initialiser_aleatoirement(pire_individu);
        distance longueur_pire_individu = permutation_calculer_distance_totale(pire_individu, matrice);
        tableau_permutation_modifier_longueur(enfants, indice_pire_individu, longueur_pire_individu);

        /* Comparaison du meilleur individu de cette génération au meilleur individu historique. */
        indice_meilleur_individu = tableau_permutation_trouver_meilleur_individu(enfants);
        meilleur_individu = tableau_permutation_obtenir_permutation(enfants, indice_meilleur_individu);
        distance longueur_meilleur_individu = permutation_calculer_distance_totale(meilleur_individu, matrice);

        if (longueur_meilleur_individu < longueur_meilleur_individu_historique)
        {
            permutation_copier(meilleur_individu_historique, meilleur_individu);
            longueur_meilleur_individu_historique = longueur_meilleur_individu;
        }

        /* Remplacement du second pire individu de cette génération par le meilleur individu historique. */
        indice_pire_individu = tableau_permutation_trouver_pire_individu(enfants);
        pire_individu = tableau_permutation_obtenir_permutation(enfants, indice_pire_individu);
        permutation_copier(pire_individu, meilleur_individu_historique);
        tableau_permutation_modifier_longueur(enfants, indice_pire_individu, longueur_meilleur_individu_historique);

        /* Remplacement de la population par ses enfants. */
        tableau_permutation_echanger_tableaux(&population, &enfants);

#ifdef AFFICHAGE_INTERACTIF
        for (size_t individu = 0; individu < nombre_individus; individu++)
        {
            Permutation permutation = tableau_permutation_obtenir_permutation(population, individu);
            afficher_permutation(sortie_interactive, permutation, 0);
            fprintf(sortie_interactive, "\n");
        }
#endif
    }

    Resultat resultat;
    resultat.permutation = meilleur_individu_historique;
    resultat.longueur = longueur_meilleur_individu_historique;

    tableau_permutation_vider(population);
    tableau_permutation_supprimer(&population);

    tableau_permutation_vider(enfants);
    tableau_permutation_supprimer(&enfants);

    return resultat;
}

Resultat tournee_genetique_dpx(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    // TODO
    return tournee_genetique_generique(matrice, nombre_individus, nombre_generations, taux_mutation);
}
