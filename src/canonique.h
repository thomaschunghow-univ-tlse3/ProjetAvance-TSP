/*
 * canonique.h
 *
 * Ce module fournit une fonction permettant de générer
 * une tournée canonique à partir d'une matrice de distances.
 */

#ifndef CANONIQUE_H
#define CANONIQUE_H

#include "structures_de_donnees.h"
#include "traitement_calcul_tournee.h"

#include <stdio.h>

Resultat calcul_tournee_canonique(MatriceDistances);

#endif // CANONIQUE_H
