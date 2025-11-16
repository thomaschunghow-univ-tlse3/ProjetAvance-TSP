/*
 * tournee_genetique.c
 */

#include "tournee_genetique.h"
#include "structure_permutation.h"
#include "structure_matrice.h"
#include "affichage.h"
#include "nombre_aleatoire.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>

void tournee_genetique_mutation(TableauPermutation population, double taux_mutation, MatriceDistance matrice)
{
    size_t nombre_individus = tableau_permutation_obtenir_nombre_permutation(population);

    /* On parcourt tous les individus de la population. */
    for (size_t indice_individu = 0; indice_individu < nombre_individus; indice_individu++)
    {
        Permutation individu = tableau_permutation_obtenir_permutation(population, indice_individu);

        size_t nombre_sommets = permutation_obtenir_taille(individu);

        /* Au lieu de parcourir tous les sommets et à chaque sommet tirer une probabilité aléatoire de muter,
         * on tire dès le début le nombre de points que l'on veut muter.
         * En fait, on approxime la loi binomiale par une loi normale. */
        size_t nombre_sommets_a_muter = (size_t)donner_reel_aleatoire_loi_normale(taux_mutation, nombre_sommets);
        nombre_sommets_a_muter /= 2;
        nombre_sommets_a_muter %= nombre_sommets;

        for (size_t i = 0; i < nombre_sommets_a_muter; i++)
        {
            /* Comme quand on échange deux points, alors deux points sont mutés,
             * donc on doit bien diviser la probabilité par deux. */
            size_t sommet_A = donner_entier_aleatoire(0, nombre_sommets);
            size_t sommet_B = donner_entier_aleatoire(0, nombre_sommets);

            permutation_echanger_sommets(individu, sommet_A, sommet_B);
        }

        distance longueur = permutation_calculer_distance_totale(individu, matrice);
        tableau_permutation_modifier_longueur(population, indice_individu, longueur);
    }
}

void tournee_genetique_selection_par_tournoi(TableauPermutation population, TableauPermutation parents, size_t taille_tournoi)
{
    size_t nombre_individus = tableau_permutation_obtenir_nombre_permutation(parents);

    for (size_t parent = 0; parent < nombre_individus; parent++)
    {
        /* Sélection de taille_tournoi individus à chaque boucle, puis mémorisation du meilleur du tournoi dans les parents. */
        size_t competiteur = donner_entier_aleatoire(0, nombre_individus);

        size_t gagnant = competiteur;
        distance longueur_gagnant = tableau_permutation_obtenir_longueur(population, gagnant);

        for (size_t tournoi = 1; tournoi < taille_tournoi; tournoi++)
        {
            competiteur = donner_entier_aleatoire(0, nombre_individus);

            distance longueur_competiteur = tableau_permutation_obtenir_longueur(population, competiteur);

            if (longueur_competiteur < longueur_gagnant)
            {
                longueur_gagnant = longueur_competiteur;
                gagnant = competiteur;
            }
        }

        Permutation tournee_gagnant = tableau_permutation_obtenir_permutation(population, gagnant);
        Permutation tournee_parent = tableau_permutation_obtenir_permutation(parents, parent);
        permutation_copier(tournee_parent, tournee_gagnant);
    }
}

void tournee_genetique_croisement_ordonne(Permutation pere, Permutation mere, Permutation enfant, Permutation inverse, size_t sommet_A, size_t sommet_B)
{
    size_t nombre_sommets = permutation_obtenir_taille(pere);

    if (sommet_B < sommet_A)
    {
        matrice_echanger_indices(&sommet_A, &sommet_B);
    }
    size_t nombre_sommets_pere_herite = sommet_B + 1 - sommet_A;

    /* Le segment copié du père est placé au début de l'enfant. */
    permutation_copier(enfant, pere);
    permutation_decaler(enfant, sommet_A);

    permutation_inverser(enfant, inverse);

    /* On remplit le reste de l'enfant avec les sommets restants dans l'ordre de la mère. */
    size_t indice_enfant = nombre_sommets_pere_herite;
    for (size_t indice_mere = 0; indice_mere < nombre_sommets; indice_mere++)
    {
        size_t sommet_mere = permutation_obtenir_sommet(mere, indice_mere);
        size_t indice_sommet_a_echanger = permutation_obtenir_sommet(inverse, sommet_mere);

        if (indice_sommet_a_echanger >= nombre_sommets_pere_herite)
        {
            permutation_echanger_sommets(enfant, indice_sommet_a_echanger, indice_enfant);
            permutation_echanger_sommets(inverse, permutation_obtenir_sommet(enfant, indice_sommet_a_echanger), permutation_obtenir_sommet(enfant, indice_enfant));
            indice_enfant++;
        }
    }
}

Resultat tournee_genetique_generique(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations, double taux_mutation, size_t taille_tournoi)
{
    size_t nombre_sommets = matrice_obtenir_nombre_points(matrice);

    TableauPermutation population = tableau_permutation_creer(nombre_individus);
    TableauPermutation enfants = tableau_permutation_creer(nombre_individus);
    TableauPermutation parents = tableau_permutation_creer(nombre_individus);

    /* Allocation mémoire de la population, des enfants, des parents et du tournoi. */
    tableau_permutation_allouer(population, nombre_sommets);
    tableau_permutation_allouer(enfants, nombre_sommets);
    tableau_permutation_allouer(parents, nombre_sommets);

    /* Initialisation de la population initiale. */
    for (size_t i = 0; i < nombre_individus; i++)
    {
        Permutation individu = tableau_permutation_obtenir_permutation(population, i);
        permutation_initialiser_aleatoirement(individu);
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

    /* Allocation mémoire de l'inverse, utilisé pour accélérer le croisement ordonné. */
    Permutation inverse = permutation_creer(nombre_sommets);

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
        /* Détermination des parents grace à une sélection par tournoi. */
        tournee_genetique_selection_par_tournoi(population, parents, taille_tournoi);

        for (size_t indice_enfant = 0; indice_enfant < nombre_individus / 2; indice_enfant++)
        {
            /* Remarque : si le nombre d'individus est impair, alors le dernier individu du tournoi ne se reproduit pas. */
            indice_enfant *= 2;
            size_t indice_pere = indice_enfant;
            size_t indice_mere = indice_pere + 1;
            size_t indice_frere = indice_pere;
            size_t indice_soeur = indice_mere;

            /* Sélection de deux parents. */
            Permutation pere = tableau_permutation_obtenir_permutation(parents, indice_pere);
            Permutation mere = tableau_permutation_obtenir_permutation(parents, indice_mere);

            /* Croisement entre les deux parents. */
            Permutation frere = tableau_permutation_obtenir_permutation(enfants, indice_frere);
            Permutation soeur = tableau_permutation_obtenir_permutation(enfants, indice_soeur);

            size_t sommet_A = donner_entier_aleatoire(0, nombre_sommets);
            size_t sommet_B = donner_entier_aleatoire(0, nombre_sommets);
            tournee_genetique_croisement_ordonne(pere, mere, frere, inverse, sommet_A, sommet_B);

            sommet_A = donner_entier_aleatoire(0, nombre_sommets);
            sommet_B = donner_entier_aleatoire(0, nombre_sommets);
            tournee_genetique_croisement_ordonne(pere, mere, soeur, inverse, sommet_A, sommet_B);
        }

        /* Mutation de l'enfant. */
        tournee_genetique_mutation(enfants, taux_mutation, matrice);

        /* Tri de la population. */
        tableau_permutation_trier(enfants);

        /* Remplacement du pire individu de cette génération par un nouvel individu. */
        size_t indice_pire_individu = nombre_individus - 1;
        Permutation pire_individu = tableau_permutation_obtenir_permutation(enfants, indice_pire_individu);
        permutation_initialiser_aleatoirement(pire_individu);
        distance longueur_pire_individu = permutation_calculer_distance_totale(pire_individu, matrice);
        tableau_permutation_modifier_longueur(enfants, indice_pire_individu, longueur_pire_individu);

        /* Comparaison du meilleur individu de cette génération au meilleur individu historique. */
        indice_meilleur_individu = 0;
        meilleur_individu = tableau_permutation_obtenir_permutation(enfants, indice_meilleur_individu);
        distance longueur_meilleur_individu = permutation_calculer_distance_totale(meilleur_individu, matrice);

        if (longueur_meilleur_individu < longueur_meilleur_individu_historique)
        {
            permutation_copier(meilleur_individu_historique, meilleur_individu);
            longueur_meilleur_individu_historique = longueur_meilleur_individu;
        }

        /* Remplacement du second pire individu de cette génération par le meilleur individu historique. */
        indice_pire_individu = nombre_individus - 2;
        pire_individu = tableau_permutation_obtenir_permutation(enfants, indice_pire_individu);
        permutation_copier(pire_individu, meilleur_individu_historique);
        tableau_permutation_modifier_longueur(enfants, indice_pire_individu, longueur_meilleur_individu_historique);

        /* Remplacement de la population par ses enfants. */
        tableau_permutation_echanger_tableaux(&population, &enfants);

#ifdef AFFICHAGE_INTERACTIF
        /* Tri de la population. */
        tableau_permutation_trier(population);

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

    tableau_permutation_vider(parents);
    tableau_permutation_supprimer(&parents);

    permutation_supprimer(&inverse);

    return resultat;
}

Resultat tournee_genetique_dpx(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    // TODO
    return tournee_genetique_generique(matrice, nombre_individus, nombre_generations, taux_mutation, nombre_individus / 2);
}
