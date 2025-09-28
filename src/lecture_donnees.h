/*
 *
 */

#ifndef LECTURE_DONNEE_H
#define LECTURE_DONNEE_H

#include "structures_de_donnees.h"

#define TAILLE_LIGNE_MAX 100

Specification lire_specification_tsp(char *nom_fichier);

TableauPoints lire_points_tsp(char *nom_fichier, size_t nombre_points);

#endif // LECTURE_DONNEE_H
