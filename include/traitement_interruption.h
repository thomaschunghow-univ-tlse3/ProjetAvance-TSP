/*
 * traitement_interruption.h
 *
 * Outil de traitement des interruptions du traitement sur le terminal.
 */

#ifndef TRAITEMENT_INTERRUPTION_H
#define TRAITEMENT_INTERRUPTION_H

#include "structure.h"

#include "calcul_distance.h"

#include <signal.h>

extern volatile sig_atomic_t interruption;

void interruption_proteger_signal(int signal, void (*traiter_signal)(int signal));

void interruption_receptionner_signal(int signal);

bool interruption_traiter_signal(Permutation permutation, Permutation permutation_minimale);

#endif // TRAITEMENT_INTERRUPTION_H