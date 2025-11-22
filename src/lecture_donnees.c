/*
 * lecture_donnees.c
 */

#include "lecture_donnees.h"
#include "calcul_distance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_LIGNE_MAX 1000

Specification lecture_initialiser_specification()
{
    Specification specification;
    memset(specification.nom, '\0', TAILLE_SPECIFICATION_MAX);
    memset(specification.type, '\0', TAILLE_SPECIFICATION_MAX);
    memset(specification.commentaire, '\0', TAILLE_SPECIFICATION_MAX);
    specification.nombre_points = 0;
    specification.calculer_distance = NULL;
    return specification;
}

void lecture_verifier_specification_valide(Specification specification)
{
    if (strcmp(specification.nom, "") == 0 ||
        strcmp(specification.nom, "") == 0 ||
        strcmp(specification.nom, "") == 0 ||
        specification.nombre_points == 0 ||
        specification.calculer_distance == NULL)
    {
        fprintf(stderr,
                "Erreur lecture_verifier_specification_valide :\n"
                "Un des champs de la spécification n'a pas été initialisé.\n");
        exit(EXIT_FAILURE);
    }
}

DistanceCalculer lecture_methode_calcul_depuis_nom(char *nom)
{
    if (strstr(nom, "EUC_2D"))
    {
        return &calculer_distance_euclidienne;
    }
    if (strstr(nom, "GEO"))
    {
        return &calculer_distance_geographique;
    }
    if (strstr(nom, "ATT"))
    {
        return &calculer_distance_euclidienne_modifiee;
    }
    fprintf(stderr,
            "Erreur lecture_methode_calcul_depuis_nom :\n"
            "Méthode de calcul non reconnue.\n");
    exit(EXIT_FAILURE);
}

Specification lecture_specification_tsp(FILE *entree)
{
    rewind(entree);
    Specification specification = lecture_initialiser_specification();
    char ligne[TAILLE_LIGNE_MAX];
    while (fgets(ligne, TAILLE_LIGNE_MAX, entree) != NULL)
    {
        if (strlen(ligne) >= TAILLE_SPECIFICATION_MAX)
        {
            fprintf(stderr,
                    "Erreur lecture_specification_tsp :\n"
                    "Ligne trop longue pour le champ de taille statique.\n");
        }
        if (strstr(ligne, "NAME"))
        {
            strncpy(specification.nom, ligne, TAILLE_SPECIFICATION_MAX);
        }
        if (strstr(ligne, "TYPE"))
        {
            strncpy(specification.type, ligne, TAILLE_SPECIFICATION_MAX);
        }
        if (strstr(ligne, "COMMENT"))
        {
            strncpy(specification.commentaire, ligne, TAILLE_SPECIFICATION_MAX);
        }
        if (strstr(ligne, "DIMENSION"))
        {
            sscanf(ligne, "%*[^0-9]%lud", &specification.nombre_points);
        }
        if (strstr(ligne, "EDGE_WEIGHT_TYPE"))
        {
            specification.calculer_distance = lecture_methode_calcul_depuis_nom(ligne);
        }
        if (strstr(ligne, "NODE_COORD_SECTION"))
        {
            break;
        }
    }
    lecture_verifier_specification_valide(specification);
    return specification;
}

void lecture_points_tsp(FILE *entree, TableauPoint tableau)
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
    size_t nombre_points = tableau_point_obtenir_nombre_points(tableau);
    for (size_t i = 0; i < nombre_points; i++)
    {
        Point point;
        fscanf(entree, "%*d%lf%lf", &(point.x), &(point.y));
        tableau_point_modifier_point(tableau, i, point);
    }
}
