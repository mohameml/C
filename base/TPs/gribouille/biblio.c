#include <stdlib.h>

#include "biblio.h"

struct biblio *creer_biblio(void)
{
	struct biblio *bib = NULL;
	return bib;
}

void liberer_biblio(struct biblio *an)
{
}


bool inserer_biblio(struct biblio * an, struct motif * M, const char *tag)
{
	return true;
}

struct motif *rechercher_biblio(struct biblio *an, const char *tag)
{
	return NULL;
}

void supprimer_biblio(struct biblio *an, const char *tag)
{
}

struct biblio *importer_biblio(const char *path)
{
    return NULL;
}

void exporter_biblio(struct biblio *an, const char *path)
{
}


void afficher_biblio(struct biblio *an)
{
}

