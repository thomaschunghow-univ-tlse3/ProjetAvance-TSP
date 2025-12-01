/*
 * structure_tableau_permutation_interne.h
 */

#ifndef STRUCTURE_TABLEAU_PERMUTATION_INTERNE_H
#define STRUCTURE_TABLEAU_PERMUTATION_INTERNE_H

#include "structure_permutation_interne.h"

#include <stddef.h>

struct tableau_permutation
{
    size_t nombre_permutations;
    struct permutation *permutations;
};

#endif // STRUCTURE_TABLEAU_PERMUTATION_INTERNE_H
