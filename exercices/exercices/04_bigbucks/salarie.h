#ifndef SALARIE_H
#define SALARIE_H

/*
    Structure de données représentant un salarié.
    Elle devra contenir, dans cet ordre :
    - son prénom sous la forme d'une chaine de caractères de longueur max 16 ;
    - son nom sous la forme d'une chaine de caractères de longueur max 32 ;
    - son age, sous la forme d'un entier non signé 8 bits ;
    - son ancienneté dans l'entreprise, sous la forme d'un entier non-signé 8 bits ;
    - son salaire mensuel, sous la forme d'un entier non signé 32 bits.
*/
struct salarie;

/* Alloue et retourne un struct salarie. */
extern struct salarie *allouer_salarie(void);

/*
    Initialise le salarié passé en paramètre.
    Le salarié s a déjà été alloué avant l'appel
    à init_salarie().
*/
extern void init_salarie(struct salarie *s,
                         const char *prenom,
                         const char *nom,
                         uint8_t age,
                         uint8_t anciennete,
                         uint32_t salaire);

/* Effectue l'allocation ET l'initialisation du salarie passé en paramètre. */
extern void creer_salarie(struct salarie **s,
                          const char *prenom,
                          const char *nom,
                          uint8_t age,
                          uint8_t anciennete,
                          uint32_t salaire);

/*
    Libère la mémoire associée au salarié passé en paramètre.
    En sortie, s doit valoir NULL.
*/
extern void plan_social(struct salarie **s);

#endif /* SALARIE_H */
