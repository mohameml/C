/*-----------------------------------------------------------------
 * collapse: fonction de contraction d'une arete
 * 
 * renvoie true si la contraction est valide, false sinon
 *
 * si la contraction est valide, met a jour le maillage et supprime
 * les primitives.
 */

#ifndef COLLAPSE_H
#define COLLAPSE_H
#include "mesh.h"
extern bool collapse_half_edge(mesh *m, half_edge *e);
#endif
