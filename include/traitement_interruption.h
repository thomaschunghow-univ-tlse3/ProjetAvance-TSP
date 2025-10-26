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

<<<<<<< HEAD
void interruption_gestionnaire(int signal);

bool interruption_traitement(Permutation permutation, Permutation permutation_minimale, distance longueur_minimale);
=======
void gestionnaire_interruption(int signal);

bool traitement_interruption(Permutation permutation, Permutation permutation_minimale, distance longueur_minimale, size_t nombre_permutations_traitees, size_t nombre_permutations_total);
>>>>>>> 20e72f5 (modification de l'arborescence)

#endif // TRAITEMENT_INTERRUPTION_H