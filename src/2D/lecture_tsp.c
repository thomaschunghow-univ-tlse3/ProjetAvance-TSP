/*
 * lecture_donnees.c
 */

#include "lecture_tsp.h"

#include "calcul_distance.h"
#include "structure_matrice.h"
#include "structure_permutation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Specification lecture_tsp_initialiser_specification()
{
    Specification specification;
    memset(specification.nom, '\0', LECTURE_TSP_TAILLE_MAX);
    memset(specification.type, '\0', LECTURE_TSP_TAILLE_MAX);
    memset(specification.commentaire, '\0', LECTURE_TSP_TAILLE_MAX);
    specification.nombre_points = 0;
    specification.distance_calculer = NULL;
    specification.distance_additionner = NULL;
    specification.distance_soustraire = NULL;
    specification.distance_comparer = NULL;
    return specification;
}

void lecture_tsp_verifier_specification_valide(Specification specification)
{
    if (strcmp(specification.nom, "") == 0 || strcmp(specification.nom, "") == 0 ||
        strcmp(specification.nom, "") == 0 || specification.nombre_points == 0 ||
        specification.distance_calculer == NULL)
    {
        fprintf(stderr, "Erreur lecture_tsp_verifier_specification_valide :\n"
                        "Un des champs de la spécification n'a pas été initialisé.\n");
        exit(EXIT_FAILURE);
    }
}

DistanceCalculer lecture_tsp_obtenir_methode_depuis_nom(char *nom)
{
    if (strstr(nom, "EUC_2D"))
    {
        return &calculer_distance_euclidienne_generique;
    }
    if (strstr(nom, "GEO"))
    {
        return &calculer_distance_geographique_generique;
    }
    if (strstr(nom, "ATT"))
    {
        return &calculer_distance_euclidienne_modifiee_generique;
    }
    fprintf(stderr, "Erreur lecture_tsp_obtenir_methode_depuis_nom :\n"
                    "Méthode de calcul non reconnue.\n");
    exit(EXIT_FAILURE);
}

Specification lecture_tsp_lire_specification(FILE *entree)
{
    rewind(entree);

    Specification specification = lecture_tsp_initialiser_specification();

    char ligne[LECTURE_TSP_TAILLE_MAX];

    while (fgets(ligne, LECTURE_TSP_TAILLE_MAX, entree) != NULL)
    {
        if (strlen(ligne) >= LECTURE_TSP_TAILLE_MAX)
        {
            fprintf(stderr, "Erreur lecture_donnees_lire_specification_tsp :\n"
                            "Ligne trop longue pour le champ de taille statique.\n");
        }
        if (strstr(ligne, "NAME"))
        {
            strncpy(specification.nom, ligne, LECTURE_TSP_TAILLE_MAX);
        }
        else if (strstr(ligne, "EDGE_WEIGHT_TYPE"))
        {
            specification.distance_calculer = lecture_tsp_obtenir_methode_depuis_nom(ligne);
        }
        else if (strstr(ligne, "TYPE"))
        {
            strncpy(specification.type, ligne, LECTURE_TSP_TAILLE_MAX);
        }
        else if (strstr(ligne, "COMMENT"))
        {
            strncpy(specification.commentaire, ligne, LECTURE_TSP_TAILLE_MAX);
        }
        else if (strstr(ligne, "DIMENSION"))
        {
            sscanf(ligne, "%*[^0-9]%lud", &specification.nombre_points);
        }
        else if (strstr(ligne, "NODE_COORD_SECTION"))
        {
            break;
        }
    }

    lecture_tsp_verifier_specification_valide(specification);
    return specification;
}

void lecture_tsp_lire_points(FILE *entree, MatriceDistance matrice)
{
    rewind(entree);

    char ligne[LECTURE_TSP_TAILLE_MAX];

    while (fgets(ligne, LECTURE_TSP_TAILLE_MAX, entree) != NULL)
    {
        if (strstr(ligne, "NODE_COORD_SECTION"))
        {
            break;
        }
    }

    size_t nombre_points = matrice_obtenir_nombre_points(matrice);

    for (size_t i = 0; i < nombre_points; i++)
    {
        Point point;
        fscanf(entree, "%*d%lf%lf", &(point.x), &(point.y));
        matrice_modifier_point(matrice, i, &point);
    }
}

void lecture_tour_lire_points(FILE *entree, Permutation permutation)
{
    rewind(entree);

    char ligne[LECTURE_TSP_TAILLE_MAX];

    while (fgets(ligne, LECTURE_TSP_TAILLE_MAX, entree) != NULL)
    {
        if (strstr(ligne, "TOUR_SECTION"))
        {
            break;
        }
    }

    size_t nombre_points = permutation_obtenir_nombre_sommets(permutation);

    for (size_t i = 0; i < nombre_points; i++)
    {
        size_t sommet;
        fscanf(entree, "%lu", &sommet);
        permutation_modifier_sommet(permutation, i, sommet - 1);
    }
}
