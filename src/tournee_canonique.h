/*
 *
 * Ce module fournit une fonction permettant de générer
 * une tournée canonique à partir d'une matrice de distances.
 */

#ifndef TOURNEE_CANONIQUE_H
#define TOURNEE_CANONIQUE_H

#include "structure_permutation.h"
#include "traitement_tournee.h"

#include <stdio.h>

Resultat calcul_tournee_canonique(MatriceDistance);

#endif // TOURNEE_CANONIQUE_H
