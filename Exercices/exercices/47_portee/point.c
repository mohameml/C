#include <stdio.h>
#include <math.h>

#include "point.h"

void afficher(struct point p)
{
    printf("(%u, %u)\n", p.x, p.y);
}

double distance_origine(struct point p)
{
    afficher(p);
    return sqrt(p.x*p.x + p.y*p.y);
}
