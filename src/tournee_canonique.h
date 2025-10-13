/*
 * tournee_canonique.h
 *
 * Ce module fournit une fonction permettant de générer
 * une tournée canonique à partir d'une matrice de distances.
 */

#ifndef TOURNEE_CANONIQUE_H
#define TOURNEE_CANONIQUE_H

#include "structures_de_donnees.h"
#include "traitement_calcul_tournee.h"

#include <stdio.h>

Resultat calcul_tournee_canonique(MatriceDistances);

#endif // TOURNEE_CANONIQUE_H
