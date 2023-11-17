/* Utilisation du préprocesseur C pour se protéger de l'inclusion multiple */
#ifndef _TABLEAU_H_
#define _TABLEAU_H_

#include <stdint.h>

/* Affiche les taille éléments du tableau tab. */
extern void affiche(int32_t tab[], uint32_t taille);

/* Initialise les taille éléments du tableau tab par des valeurs
 * entières entrées au clavier par l'utilisateur. */
extern void init_interactive(int32_t tab[], uint32_t taille);

/* Initialise les taille éléments du tableau tab par des valeurs
 * entières tirées aléatoirement. */
extern void init_aleatoire(int32_t tab[], uint32_t taille);

/* Trie le tableau tab à l'aide de l'algorithme de tri par
 * insertion. */
extern void tri_insertion(int32_t tab[], uint32_t taille);

#endif /* _TABLEAU_H_ */
