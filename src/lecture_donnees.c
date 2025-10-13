/*
 * lecture_donnees.c
 */

#include "lecture_donnees.h"
#include "calcul_distance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_LIGNE_MAX 100

Specification initialiser_specification()
{
    Specification specification;
    memset(specification.nom, '\0', TAILLE_CHAMP_MAX);
    memset(specification.type, '\0', TAILLE_CHAMP_MAX);
    memset(specification.commentaire, '\0', TAILLE_CHAMP_MAX);
    specification.nombre_points = 0;
    specification.calculer_distance = NULL;
    return specification;
}

void verifier_specification_valide(Specification specification)
{
    if (strcmp(specification.nom, "") == 0 ||
        strcmp(specification.nom, "") == 0 ||
        strcmp(specification.nom, "") == 0 ||
        specification.nombre_points == 0 ||
        specification.calculer_distance == NULL)
    {
        fprintf(stderr,
                "Erreur verifier_specification_valide :\n"
                "Un des champs de la spécification n'a pas été initialisé.\n");
        exit(EXIT_FAILURE);
    }
}

FonctionCalculDistance methode_calcul_depuis_nom(char *nom)
{
    if (strstr(nom, "EUC_2D"))
    {
        return liste_fonctions_calcul[EUC_2D];
    }
    if (strstr(nom, "GEO"))
    {
        return liste_fonctions_calcul[GEO];
    }
    if (strstr(nom, "ATT"))
    {
        return liste_fonctions_calcul[ATT];
    }
    fprintf(stderr,
            "Erreur methode_calcul_depuis_nom :\n"
            "Méthode de calcul non reconnue.\n");
    exit(EXIT_FAILURE);
}

Specification lire_specification_tsp(FILE *entree)
{
    rewind(entree);
    Specification specification = initialiser_specification();
    char ligne[TAILLE_LIGNE_MAX];
    while (fgets(ligne, TAILLE_LIGNE_MAX, entree) != NULL)
    {
        if (strlen(ligne) >= TAILLE_CHAMP_MAX)
        {
            fprintf(stderr,
                    "Erreur lire_specification_tsp :\n"
                    "Ligne trop longue pour le champ de taille statique.\n");
        }
        if (strstr(ligne, "NAME"))
        {
            strcpy(specification.nom, ligne);
        }
        if (strstr(ligne, "TYPE"))
        {
            strcpy(specification.type, ligne);
        }
        if (strstr(ligne, "COMMENT"))
        {
            strcpy(specification.commentaire, ligne);
        }
        if (strstr(ligne, "DIMENSION"))
        {
            sscanf(ligne, "%*[^0-9]%ld", &specification.nombre_points);
        }
        if (strstr(ligne, "EDGE_WEIGHT_TYPE"))
        {
            specification.calculer_distance = methode_calcul_depuis_nom(ligne);
        }
        if (strstr(ligne, "NODE_COORD_SECTION"))
        {
            break;
        }
    }
    verifier_specification_valide(specification);
    return specification;
}

void lire_points_tsp(FILE *entree, TableauPoints tableau)
{
    rewind(entree);
    char ligne[TAILLE_LIGNE_MAX];
    while (fgets(ligne, TAILLE_LIGNE_MAX, entree) != NULL)
    {
        if (strstr(ligne, "NODE_COORD_SECTION"))
        {
            break;
        }
    }
    size_t nombre_points = taille_tableau_points(tableau);
    for (size_t i = 0; i < nombre_points; i++)
    {
        Point *point = obtenir_element_tableau_points(tableau, i);
        fscanf(entree, "%*d%lf%lf", &(point->x), &(point->y));
    }
}