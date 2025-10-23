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

void gestionnaire_interruption(int signal);

bool traitement_interruption(Permutation permutation, Permutation permutation_minimale, distance longueur_minimale);

#endif // TRAITEMENT_INTERRUPTION_H