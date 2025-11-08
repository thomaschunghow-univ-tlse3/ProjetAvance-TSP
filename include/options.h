/*
 * options.h
 *
 * Outil de lecture et de validation des arguments du programme.
 * Permet l'ouverture et la fermeture des fichiers de manière sécurisée
 * et de convertir le nom d'une méthode de calcul en énumération interne.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
#include <stdio.h>

#define TAILLE_OPTIONS_MAX 100

typedef enum
{
    CANONIQUE,
    FORCE_BRUTE,
    PLUS_PROCHE_VOISIN,
    MARCHE_ALEATOIRE,
    PLUS_PROCHE_VOISIN_2_OPTIMISATION,
    MARCHE_ALEATOIRE_2_OPTIMISATION,
    GENETIQUE_GENERIQUE,
    GENETIQUE_DPX,
    TOUTES,
} MethodeCalcul;

typedef struct
{
    size_t nombre_individus;
    size_t nombre_generations;
    double taux_mutation;
} ArgumentsGenetique;

typedef struct
{
    char nom_fichier_entree[TAILLE_OPTIONS_MAX];
    char nom_fichier_sortie[TAILLE_OPTIONS_MAX];
    bool canonique;
    MethodeCalcul methode_calcul;
    ArgumentsGenetique arguments_genetique;
} Options;

Options options_traitement(int argc, char **argv);

FILE *ouverture_entree(Options options);
FILE *ouverture_sortie(Options options);

void fermeture_entree(FILE *, Options options);
void fermeture_sortie(FILE *, Options options);

#ifdef AFFICHAGE_INTERACTIF
extern FILE *sortie_interactive;
#endif // AFFICHAGE_INTERACTIF

#endif // OPTIONS_H
