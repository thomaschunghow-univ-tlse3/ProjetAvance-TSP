/*
 * traitement_interruption.h
 *
 * Outil de traitement des interruptions du traitement sur le terminal.
 */

#ifndef TRAITEMENT_INTERRUPTION_H
#define TRAITEMENT_INTERRUPTION_H

#include "structure_permutation.h"

#include <signal.h>

extern volatile sig_atomic_t interruption;

void interruption_gestionnaire(int signal);

bool interruption_traitement(Permutation permutation, Permutation permutation_minimale, distance longueur_minimale, size_t nombre_permutations_traitees, size_t nombre_permutations_total);

#endif // TRAITEMENT_INTERRUPTION_H