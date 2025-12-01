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

#define OPTIONS_TAILLE_MAX 100

typedef enum
{
    CANONIQUE,
    FORCE_BRUTE,
    PLUS_PROCHE_VOISIN,
    MARCHE_ALEATOIRE,
    PLUS_PROCHE_VOISIN_2_OPTIMISATION,
    MARCHE_ALEATOIRE_2_OPTIMISATION,
    GENETIQUE_LIGHT,
    GENETIQUE_DPX,
    TOUTES,
} Methode;

typedef struct
{
    size_t nombre_individus;
    size_t nombre_generations;
    double taux_mutation;
} ArgumentsGenetique;

typedef struct
{
    char nom_fichier_entree[OPTIONS_TAILLE_MAX];
    char nom_fichier_sortie[OPTIONS_TAILLE_MAX];
    bool canonique;
    Methode methode_calcul;
    ArgumentsGenetique arguments_genetique;
} Arguments;

Arguments options_traiter_arguments(int argc, char **argv);

extern FILE *entree;
extern FILE *sortie;

void fichier_ouvrir_entree(Arguments options);
void fichier_ouvrir_sortie(Arguments options);

void fichier_fermer_entree(Arguments options);
void fichier_fermer_sortie(Arguments options);

#endif // OPTIONS_H
