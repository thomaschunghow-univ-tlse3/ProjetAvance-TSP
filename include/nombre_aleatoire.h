/*
 * nombre_aleatoire.h
 *
 * Fonctions de génération de nombres aléatoires.
 */

#ifndef NOMBRE_ALEATOIRE_H
#define NOMBRE_ALEATOIRE_H

#include <stdlib.h>

size_t donner_entier_aleatoire(size_t borne_inf, size_t borne_sup);

double donner_reel_aleatoire(double borne_inf, double borne_sup);

double donner_reel_aleatoire_loi_normale(double probabilite, size_t nombre_tirages);

#endif // NOMBRE_ALEATOIRE_H
