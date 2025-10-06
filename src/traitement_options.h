/*
 *
 */

#ifndef TRAITEMENT_OPTIONS_H
#define TRAITEMENT_OPTIONS_H

#include <stdbool.h>

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
    ALL
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

#endif // TRAITEMENT_OPTIONS_H