/*
 *
 * Ce module permet de lire et valider les arguments du programme,
 * d'ouvrir et de fermer les fichiers de manière sécurisée
 * et de convertir le nom d'une méthode de calcul en énumération interne.
 */

#ifndef TRAITEMENT_OPTIONS_H
#define TRAITEMENT_OPTIONS_H

#include <stdbool.h>
#include <stdio.h>

#define TAILLE_OPTIONS_MAX 100

typedef enum
{
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
    bool est_donne_fichier_entree;
    bool est_donne_fichier_sortie;
    bool est_donne_methode_calcul;
    bool est_donne_canonique;

    char nom_fichier_entree[TAILLE_OPTIONS_MAX];
    char nom_fichier_sortie[TAILLE_OPTIONS_MAX];
    MethodeCalcul methode_calcul;
} Options;

Options traitement_options(int argc, char **argv);

FILE *ouverture_entree(Options options);
FILE *ouverture_sortie(Options options);
void fermeture_entree(FILE *, Options options);
void fermeture_sortie(FILE *, Options options);

#endif // TRAITEMENT_OPTIONS_H