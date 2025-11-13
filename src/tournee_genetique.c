#include "tournee_genetique.h"
#include "structure_permutation.h" //
#include "structure_matrice.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>

/*Création des fonctions auxiliaires*/

static void permutation_aleatoire(Permutation p)
{
    size_t i, j;
    size_t n = permutation_obtenir_taille(p);
    for (i = n - 1; i > 1; i--)
    {
        j = 1 + (rand() % i);
        permutation_echanger_sommets(p, i, j);
    }
}

static void mutation_echange(Permutation individu, double taux_mutation)
{
    size_t n = permutation_obtenir_taille(individu);
    for (size_t i = 1; i < n; i++)
    {
        if ((double)rand() / RAND_MAX < taux_mutation)
        {
            size_t j = 1 + (rand() % (n - 1));
            if (i != j)
            {
                permutation_echanger_sommets(individu, i, j);
            }
        }
    }
}

static Permutation selection_par_tournoi(Permutation *population, size_t nombre_individus, MatriceDistance m, size_t taille_tournoi)
{
    Permutation meilleur_competiteur = NULL;
    distance meilleure_longueur = DBL_MAX;

    for (size_t t = 0; t < taille_tournoi; t++)
    {
        Permutation competiteur = population[rand() % nombre_individus];
        distance longueur_competiteur = permutation_calculer_distance_totale(competiteur, m);

        if (meilleur_competiteur == NULL || longueur_competiteur < meilleure_longueur)
        {
            meilleure_longueur = longueur_competiteur;
            meilleur_competiteur = competiteur;
        }
    }
    return meilleur_competiteur;
}

Resultat tournee_genetique_generique(MatriceDistance m, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    srand((unsigned int)time(NULL)); //

    const size_t nb_villes = matrice_obtenir_nombre_points(m);

    Permutation *population = (Permutation *)malloc(nombre_individus * sizeof(Permutation));
    if (!population)
    {
        perror("Échec allocation population");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < nombre_individus; i++)
    { // Initialisation de la population
        population[i] = permutation_creer(nb_villes);
        permutation_aleatoire(population[i]);
    }

    Resultat meilleur_resultat;
    meilleur_resultat.permutation = permutation_creer(nb_villes);
    meilleur_resultat.longueur = DBL_MAX;

    for (size_t i = 0; i < nombre_individus; i++)
    { // Évaluation initiale
        distance longueur = permutation_calculer_distance_totale(population[i], m);
        if (longueur < meilleur_resultat.longueur)
        {
            meilleur_resultat.longueur = longueur;
            permutation_copier(meilleur_resultat.permutation, population[i]);
        }
    }

    for (size_t g = 0; g < nombre_generations; g++)
    { // Boucle principale de l'algorithme génétique
        Permutation *generation_suivante = (Permutation *)malloc(nombre_individus * sizeof(Permutation));
        if (!generation_suivante)
        {
            perror("Échec allocation génération suivante");
            break;
        }

        size_t taille_tournoi = 5;
        if (taille_tournoi > nombre_individus)
            taille_tournoi = nombre_individus;

        for (size_t i = 0; i < nombre_individus; i++)
        { // Création de la nouvelle génération
            Permutation parent = selection_par_tournoi(population, nombre_individus, m, taille_tournoi);

            generation_suivante[i] = permutation_creer(nb_villes);
            permutation_copier(generation_suivante[i], parent);

            mutation_echange(generation_suivante[i], taux_mutation);
        }

        for (size_t i = 0; i < nombre_individus; i++)
        {
            permutation_supprimer(&population[i]);
        }
        free(population);
        population = generation_suivante;

        for (size_t i = 0; i < nombre_individus; i++)
        {
            distance longueur = permutation_calculer_distance_totale(population[i], m);
            if (longueur < meilleur_resultat.longueur)
            {
                meilleur_resultat.longueur = longueur;
                permutation_copier(meilleur_resultat.permutation, population[i]);
            }
        }
    }

    for (size_t i = 0; i < nombre_individus; i++)
    {
        permutation_supprimer(&population[i]);
    }
    free(population);

    return meilleur_resultat;
}

Resultat tournee_genetique_dpx(MatriceDistance m, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    return tournee_genetique_generique(m, nombre_individus, nombre_generations, taux_mutation); // A remplacer par une vraie implémentation DPX
}