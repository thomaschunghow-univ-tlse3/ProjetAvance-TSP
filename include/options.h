/*
 * options.h
 *
 * Outil de lecture et de validation des arguments du programme.
 * Permet l'ouverture et la fermeture des fichiers de manière sécurisée
 * et de convertir le nom d'une méthode de calcul en énumération interne.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

<<<<<<< HEAD

=======
>>>>>>> 20e72f5 (modification de l'arborescence)
#include <stdbool.h>
#include <stdio.h>

#define TAILLE_OPTIONS_MAX 100

typedef enum
{
    CANONIQUE,
<<<<<<< HEAD
    FORCE_BRUTE,
    PLUS_PROCHE_VOISIN,
    MARCHE_ALEATOIRE,
    PLUS_PROCHE_VOISIN_2_OPTIMISATION,
    MARCHE_ALEATOIRE_2_OPTIMISATION,
    GENETIQUE_GENERIQUE,
    GENETIQUE_DPX,
    TOUTES,
=======
    BF,
    NN,
    RW,
    NN2OPT,
    RW2OPT,
    GA,
    GADPX,
    ALL,
>>>>>>> 20e72f5 (modification de l'arborescence)
} MethodeCalcul;

typedef struct
{
    char nom_fichier_entree[TAILLE_OPTIONS_MAX];
    char nom_fichier_sortie[TAILLE_OPTIONS_MAX];
    bool canonique;
    MethodeCalcul methode_calcul;
} Options;

<<<<<<< HEAD
Options options_traitement(int argc, char **argv);
=======
Options traitement_options(int argc, char **argv);
>>>>>>> 20e72f5 (modification de l'arborescence)

FILE *ouverture_entree(Options options);
FILE *ouverture_sortie(Options options);

void fermeture_entree(FILE *, Options options);
void fermeture_sortie(FILE *, Options options);

#endif // OPTIONS_H