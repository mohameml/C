#ifndef _LDC_H_
#define _LDC_H_

#include <stdint.h>

// La structure représentant un élément de la liste doublement
// chaînée
struct ldc {
    uint8_t numero;
    struct ldc* suiv;
    struct ldc* prev;
};

// Insère la valeur n en fin de la liste pointée par pl
extern void ldc_insere_fin(struct ldc** pl, uint32_t n);

// Affiche le contenu de la liste l
extern void ldc_affiche(struct ldc* l);

// Retourne le nombre d'éléments contenus dans liste l
extern uint32_t ldc_taille(struct ldc* l);

// Retourne l'élément placé n positions après e
// préconditions:
//   - e non NULL
//   - il y a au moins n éléments après e
extern struct ldc* ldc_recupere_nieme(struct ldc* e, uint8_t n);

// Supprime l'élément e de la liste pointée par pl
// et libère la mémoire associée à e.
// préconditions:
//   - *pl non vide
//   - e non NULL
//   - e dans *pl
extern void ldc_supprime(struct ldc** pl, struct ldc* e);

// Libère la mémoire occupée par chacun des éléments
// de la liste l.
extern void ldc_libere(struct ldc* l);

#endif /* _LDC_H_ */
