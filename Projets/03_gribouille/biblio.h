#ifndef _BIBLIO_
#define _BIBLIO_
#include "motif.h"
#include <inttypes.h>
#include <stdbool.h>

/* Type biblio
 * Une structure de donnees permettant de stocker une bibliotheque de motifs,
 * contenant pour chaque motif stocke : un motif et un tag associe (chaine de
 * caractere identifiant de maniere unique un objet).
 * Remarque: on declare ici le type biblio sans le definir. La definition du
 * type se fera dans biblio.c, ce qui permet de garantir l'encapsulation:
 * on ne peut acceder ou modifier une variable de type biblio que via les
 * fonctions definies dans biblio.h. En revanche, le type biblio ne peut
 * apparaitre dans les profils des fonctions et dans un code utilisant ce 
 * module que sous forme d'un "pointeur vers biblio" (car la taille de la 
 * structure elle-meme n'est pas connue).
 */
struct biblio;

/* Cree une nouvelle bibliotheque, initialement vide. */
extern struct biblio *creer_biblio(void);

/* Libere toute la memoire utilisee par la biblitheque pointee par
 * bib. */
extern void liberer_biblio(struct biblio *bib);

/*  Associe le motif pointe par m a la chaine de caracteres tag dans
 *  la bibliotheque pointee par bib.  Si la bibliotheque contenait
 *  deja une entree de cle "tag", l'association n'est pas realisee et
 *  la fonction retourne false. En cas d'insertion, le motif est
 *  egalement sauvegarde dans un fichier au format PPM.  */
extern bool inserer_biblio(struct biblio *bib, struct motif *m, const char *tag);

/* Retourne un pointeur vers le motif associe a la cle "tag" dans la
 * bibliotheque pointee par bib ou NULL si la cle est absente. */
extern struct motif *rechercher_biblio(struct biblio *bib, const char *tag);

/* Supprime l'entree de cle tag et detruit le motif associe si tag 
 * est presente dans la bibliotheque pointee par bib, sans effet sinon. */
extern void supprimer_biblio(struct biblio *bib, const char *tag);

/* Sauvegarde le contenu de la bibliotheque pointee par bib dans le
 * fichier nomme path. */
extern void exporter_biblio(struct biblio *bib, const char *path);

/* Alloue une bibliotheque et l'initialise en fonction du contenu du
 * fichier de sauvegarde path.  Renvoie un pointeur vers cette
 * bibliotheque. */
extern struct biblio *importer_biblio(const char *path);

/* Debug purpose. */
extern void afficher_biblio(struct biblio *bib);

#endif

