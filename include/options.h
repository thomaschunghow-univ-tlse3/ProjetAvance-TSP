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
    BF,
    NN,
    RW,
    NN2OPT,
    RW2OPT,
    GA,
    GADPX,
    ALL,
} MethodeCalcul;

typedef struct
{
    char nom_fichier_entree[TAILLE_OPTIONS_MAX];
    char nom_fichier_sortie[TAILLE_OPTIONS_MAX];
    bool canonique;
    MethodeCalcul methode_calcul;
} Options;

Options traitement_options(int argc, char **argv);

FILE *ouverture_entree(Options options);
FILE *ouverture_sortie(Options options);

void fermeture_entree(FILE *, Options options);
void fermeture_sortie(FILE *, Options options);

#endif // OPTIONS_H