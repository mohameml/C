#include <stdlib.h>

#include "motif.h"

struct motif *creer_motif(uint16_t L, uint16_t H, couleur BG)
{
    return NULL;
}

struct motif *copier_motif(struct motif *src)
{
    return NULL;
}

void init_motif(struct motif *M, couleur BG)
{
}


void detruire_motif(struct motif *M)
{
}


void tracer_droite(struct motif *M, struct droite *D)
{
}


void tracer_cercle(struct motif *M, struct cercle *arc)
{
}

void afficher_motif(struct motif *M)
{
}

void exporter_PPM(struct motif *M, const char *path)
{
}

struct motif *importer_PPM(const char *path)
{
    return NULL;
}


void remplir(struct motif *M, struct point *P, couleur coul)
{
}

void pivoter(struct motif *M, dir arrivee)
{
}

void retourner(struct motif *M, axe arrivee)
{
}
