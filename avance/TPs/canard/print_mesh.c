/* Fonctions d'affichage
 */

#include "print_mesh.h"
#include "list.h"

void print_half_edge_ptr(struct half_edge *e)
{
    if (!e)
        printf("NULL");
    else
        printf("HE[%02d]", list_alloc_identifier(e));
}

void print_face_ptr(struct face *f)
{
    if (!f)
        printf("NULL");
    else
        printf("F[%02d]", list_alloc_identifier(f));
}

void print_vertex_ptr(struct vertex *v)
{
    if (!v)
        printf("NULL");
    else
        printf("V[%02d]", list_alloc_identifier(v));
}


void print_half_edge(struct half_edge *e)
{
    print_half_edge_ptr(e);
    if (e) {
        printf(" { vertex="); print_vertex_ptr(e->vertex);
        printf("\tpair=");  print_half_edge_ptr(e->pair);
        printf("\tprev=");  print_half_edge_ptr(e->prev);
        printf("\tnext=");  print_half_edge_ptr(e->next);
        printf("\tface=");  print_face_ptr(e->face);
        printf(" }");
    }
    printf("\n");
}

void print_face(struct face *f)
{
    print_face_ptr(f);
    if (f) {
        printf(" { \t\tedges=(");

        // print edges
        struct half_edge *e = f->edges;

        // infinite loop breaker
        uint32_t it = MAX_LOOP;
        do {
            print_half_edge_ptr(e);
            printf(" ");
            e = e->next;
        } while (e != f->edges && e != 0 && --it > 0);

        if (it == 0)
            printf(" ... ");
        printf(") }");
    }
    printf("\n");
}

void print_vertex(struct vertex *v)
{
    print_vertex_ptr(v);
    if (v) {
        printf(" { (%f,%f,%f) \t\tleaving_edge=(", v->x, v->y, v->z);

        // print edges
        struct half_edge *e = v->leaving_edge;
        // infinite loop breaker
        uint32_t it = 15;

        do {
            print_half_edge_ptr(e);
            printf(" ");
            if (!e || !e->pair)
                break;
            e = e->pair->next;
        } while (e != v->leaving_edge && e && --it > 0);

        if (it == 0)
            printf(" ... ");
        printf(") }");
    }

    printf("\n");
}

void print_mesh(struct mesh *m)
{
    if (!m)
        printf("NULL mesh pointer\n");
    else {

        printf("mesh {\n");
        printf("\t\tvertex_size=%d\t\tface_size=%d\t\thalf_edge_size=%d\n",
               list_size(m->vertices),
               list_size(m->faces),
               list_size(m->hedges));

        list_FOR_EACH(m->vertices, struct vertex *, v)
            print_vertex(v);

        list_FOR_EACH(m->faces, struct face *, f)
            print_face(f);

        list_FOR_EACH(m->hedges, struct half_edge *, e)
            print_half_edge(e);

        printf("}\n");
    }
}
