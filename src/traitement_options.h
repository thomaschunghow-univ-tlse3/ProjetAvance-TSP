/*
 *
 */

#ifndef TRAITEMENT_OPTIONS_H
#define TRAITEMENT_OPTIONS_H

#include <stdbool.h>

#define TAILLE_OPTIONS_MAX 200

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
    bool fichier_entree_fourni;
    bool fichier_sortie_fourni;
    bool methode_calcul_fourni;
    bool tournee_canonique;

    char nom_fichier_entree[TAILLE_OPTIONS_MAX];
    char nom_fichier_sortie[TAILLE_OPTIONS_MAX];
    MethodeCalcul methode_calcul;
} Options;

Options traitement_options(int argc, char **argv);

#endif // TRAITEMENT_OPTIONS_H