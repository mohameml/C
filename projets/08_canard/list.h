/*
 * structure de double liste chainee
 * gere l'allocation desallocation de donnees

 * les donnees de chaque element sont initialisees a zero

 * listes "concises", les pointeurs de donnees/elements crees servent
 * directement a iterer/naviguer dans la liste (le pointeur de donnees
 * d'un element suffit a caracteriser l'element de la liste)

 * toute operation en temps constant O(1) sauf indication contraire
 */

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdint.h>

/* definition de liste a partir d'une structure privee dans le .c */
struct list;

/* -----------------------------------------------------------------
 * creation et liberation
 */

/* stipule la taille de chaque element alloue dans la liste */
extern struct list *list_create(uint32_t max_elem_size_in_bytes);
extern void list_free(struct list *l);

/* -----------------------------------------------------------------
 * fonctions d'insertions
 *
 * le pointeur de donnees fourni pour le contenu d'un element doit
 * etre initialise; les donnees de ce pointeur seront copiees dans le
 * nouvel element cree, c'est a dire a l'adresse du pointeur renvoye
 * par chacune de ces fonctions
 */

/* inserer un element avant un autre element "before_data" */
extern void *list_insert(struct list *l, void *before_data, void *data);

extern void *list_push_back(struct list *l, void *data);
extern void *list_push_front(struct list *l, void *data);

/* -----------------------------------------------------------------
 * function permettant la suppression et liberation d'un element de la
 * liste
 */

/* suppression de l'element data: la fonction renvoie un pointeur sur
 * le successeur de data */
extern void *list_erase(struct list *l, void *data);

/* sort un element en tete ou queue de liste */
extern void list_pop_front(struct list *l);
extern void list_pop_back(struct list *l);

/* -----------------------------------------------------------------
 *
 * deplace un element dans une liste sans allocation / realloction en
 * le reinserant avant "before_data"
 *
 * l'insertion d'un element avant ou apres lui-meme est sans effet
 *
 * (precondition) src_data et before_data appartiennent a la meme
 * liste
 */

extern void list_move(void *src_data, void *before_data);

/* -----------------------------------------------------------------
 * fonction d'acces
 */

/* premier element */
extern void *list_front(struct list *l);

/* pointeur de fin (conceptuellement APRES le dernier element de la
 * liste - utilise pour verifier la fin d'un parcours direct ou
 * inverse de la liste) */
extern void *list_end(struct list *l);

/* dernier element de la liste */
extern void *list_back(struct list *l);

/* macros de parcours de liste. __l=liste, __enum_var_type est le type
 * du pointeur d'iteration, __enum_var_name le nom de la variable
 * d'iteration
 */
#define list_FOR_EACH(__l,__enum_var_type,__enum_var_name)      \
    for (__enum_var_type __enum_var_name=list_front(__l);       \
         __enum_var_name!=list_end(__l);                        \
         __enum_var_name=list_next(__enum_var_name))

#define list_FOR_EACH_REVERSE(__l,__enum_var_type,__enum_var_name)	\
    for (__enum_var_type __enum_var_name=list_back(__l);		\
         __enum_var_name!=list_end(__l);				\
         __enum_var_name=list_previous(__enum_var_name))

/* renvoie le i-eme element de la liste */
extern void *list_element(struct list *l, uint32_t i);

/* renvoie l'indice de l'element "data" dans la liste entre 0..l-1 :
   O(list_size(l)) */
extern uint32_t list_get_index(struct list *l, void *data);

/* taille de la liste (acces a temps constant) */
extern uint32_t list_size(const struct list *l);

/* -----------------------------------------------------------------
 * acces et parcours
 */

/* renvoie les donnees du predecesseur de l'element "data" */
extern void *list_previous(void *data);

/* renvoie le successeur de l'element "data" */
extern void *list_next(void *data);

/* renvoie une signature lisible de l'element : un numero d'allocation
 * en mode DEBUG, un pointeur tronque pour lecture en mode
 * RELEASE. Utile pour l'affichage concis permettant d'identifier un
 * element alloue */
extern uint32_t list_alloc_identifier(void *data);

/* -----------------------------------------------------------------
 * tris
 *
 * il faut fournir un pointeur sur une fonction less_than renvoyant le
 * resultat d'une comparaison de deux elements de la liste
 */

/* tri fusion Theta(n log n) */
extern void list_merge_sort(struct list *l, bool (*less_than)(void *data1, void *data2));

/* tri insertion O(n^2), mais ~O(n) en moyenne sur une liste
 * quasi-triee */
extern void list_insertion_sort(struct list *l, bool (*less_than)(void *data1, void *data2));

/* testeur : la liste est-elle triee? */
extern bool list_sorted(struct list *l, bool (*less_than)(void *data1, void *data2));

#endif //LIST_H
