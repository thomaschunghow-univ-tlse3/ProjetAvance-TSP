#ifndef TRAITEMENT_INTERRUPTION_H
#define TRAITEMENT_INTERRUPTION_H

#include "structures_permutations.h" // Pour Permutation et distance
#include <signal.h> // Pour sig_atomic_t
#include <stdbool.h> // Pour bool
#include <stddef.h> // Pour size_t

extern volatile sig_atomic_t flag;


void changement_etat(int signal);


void gerer_interruption_bf(distance d_courante,distance d_minimale,Permutation meilleure_permutation,Permutation permutation_courante,bool *stop);

#endif // TRAITEMENT_INTERRUPTION_H