/* fonction de debogage: affichage compact de chaque primitive */

#ifndef PRINT_MESH_H
#define PRINT_MESH_H

#include "mesh.h"

/* affichage de pointeurs d'une primitive */
extern void print_half_edge_ptr(struct half_edge *e);
extern void print_face_ptr(struct face *f);
extern void print_vertex_ptr(struct vertex *v);

/* affichage d'une structure */
extern void print_half_edge(struct half_edge *e);
extern void print_face(struct face *f);
extern void print_vertex(struct vertex *v);

/* affichage d'un maillage complet */
extern void print_mesh(struct mesh *m);

#endif /* PRINT_MESH_H */
