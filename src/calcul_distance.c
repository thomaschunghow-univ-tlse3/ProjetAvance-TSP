/*
 *
 */

#include "calcul_distance.h"

#include <stdio.h>
#include <math.h>

distance calcul_distance_euclidienne(Point A, Point B)
{
    return hypot(B.x - A.x, B.y - A.y);
}
