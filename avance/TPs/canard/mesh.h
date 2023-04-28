#ifndef MESH_H
#define MESH_H

#include "list.h"

/* definition d'une demi-arete (half-edge) */
struct half_edge {
    struct half_edge *next;          /* prochain half-edge dans la face */
    struct half_edge *prev;          /* predecesseur du half-edge dans la face */
    struct vertex    *vertex;        /* sommet vers lequel pointe ce half-edge */
    struct face      *face;          /* face a laquelle appartient ce half-edge */
    struct half_edge *pair;          /* half-edge jumeau */
    /* donnees supplementaires possibles ici */
};

/* definition d'un sommet (vertex) */
struct vertex {
    float x, y, z;              /* coordonnees du sommet */
    struct half_edge *leaving_edge;  /* une demi-arete partant de ce sommet */
};

/* definition d'une face (=polygone) */
struct face {
    struct half_edge *edges;         /* un element de la liste des demi-aretes */
};

/* definition d'un maillage */
struct mesh {
    struct list *vertices;
    struct list *faces;
    struct list *hedges;
};

#endif
