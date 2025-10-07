/*
 *
 */

#include "lecture_donnees.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Specification lire_specification_tsp(char *nom_fichier)
{
    Specification specification;
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        fprintf(stderr,
                "Erreur lire_specification_tsp :\n"
                "Echec d'ouverture du fichier %s.\n",
                nom_fichier);
        exit(EXIT_FAILURE);
    }
    char ligne[TAILLE_LIGNE_MAX];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        if (strlen(ligne) >= TAILLE_CHAMP_MAX)
        {
            fprintf(stderr,
                    "Erreur lire_specification_tsp :\n"
                    "Ligne trop longue pour le champ de taille statique.\n");
        }
        if (strstr(ligne, "NAME"))
        {
            sscanf(ligne, "%*[^:]:%s", specification.nom);
        }
        if (strstr(ligne, "TYPE"))
        {
            sscanf(ligne, "%*[^:]:%s", specification.type);
        }
        if (strstr(ligne, "COMMENT"))
        {
            sscanf(ligne, "%*[^:]:%s", specification.commentaire);
        }
        if (strstr(ligne, "DIMENSION"))
        {
            sscanf(ligne, "%*[^0-9]%ld", &specification.nombre_points);
        }
        if (strstr(ligne, "EDGE_WEIGHT_TYPE"))
        {
            sscanf(ligne, "%*[^:]:%s", specification.type_distance);
        }
        if (strstr(ligne, "NODE_COORD_SECTION"))
        {
            break;
        }
    }
    if(fclose(fichier) == -1){
		perror("fermeture fichier lire specification");
		exit(0);
	}
    return specification;
}

void lire_points_tsp(char *nom_fichier, TableauPoints tableau)
{
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        fprintf(stderr,
                "Erreur lire_points_tsp :\n"
                "Echec d'ouverture du fichier %s.\n",
                nom_fichier);
        exit(EXIT_FAILURE);
    }
    char ligne[TAILLE_LIGNE_MAX];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        if (strstr(ligne, "NODE_COORD_SECTION"))
        {
            break;
        }
    }
    for (size_t i = 0; i < tableau.nombre_points; i++)
    {
        fscanf(fichier, "%*d%lf%lf", &(tableau.points[i].x), &(tableau.points[i].y));
    }
    if(fclose(fichier) == -1){
		perror("fermeture fichier lire point");
		exit(0);
	}
}