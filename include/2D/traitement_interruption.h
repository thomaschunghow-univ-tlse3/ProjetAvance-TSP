/*
 * traitement_interruption.h
 *
 * Outil de traitement des interruptions du traitement sur le terminal.
 */

#ifndef TRAITEMENT_INTERRUPTION_H
#define TRAITEMENT_INTERRUPTION_H

#include "options.h"
#include "structure_permutation.h"

#include <signal.h>
#include <time.h>

/* TODO : Rendre l'interruption générique, c'est-à-dire de ne pas avoir à la déclarer dans la partie générique du code. */
extern Permutation permutation_courante;
extern Permutation permutation_resultat;
extern clock_t temps_initial;
extern Arguments arguments;
extern MatriceDistance matrice;

void interruption_proteger_signal(int signal, void (*traiter_signal)(int signal), struct sigaction *ancienne_action);
void interruption_retablir_masque(int signal, struct sigaction *action);

void interruption_force_brute_traiter_signal(int signal);

void interruption_2_optimisation_traiter_signal(int signal);

#endif // TRAITEMENT_INTERRUPTION_H
