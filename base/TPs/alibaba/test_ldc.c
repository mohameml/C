/*
    Module de test de ldc.c utilisant la bibliothèque Criterion.

    Ces tests utilisent deux macros :
    - cr_assert(cond) qui arrête le programme si cond est fausse ;
    - cr_expect(cond) qui indique que le test courant a échoué si cond est fausse.

    ATTENTION :
    Ces détails sont donnés à titre d'information, on ne s'attend pas à ce que vous
    complétiez ce fichier. Néanmoins, si vous souhaitez rajouter vos propres tests,
    n'hésitez pas surtout pas !
*/

#include <stdlib.h>
#include <stdint.h>
#include <criterion/criterion.h>

#include "ldc.h"

static struct ldc* create_empty_list() {
    return NULL;
}

static struct ldc* create_singleton_list() {
    struct ldc* trois = malloc(sizeof(struct ldc));
    trois->prev = trois;
    trois->suiv = trois;
    trois->numero = 3;
    return trois;
}

static struct ldc* create_preums_list() {
    struct ldc* trois = malloc(sizeof(struct ldc));
    struct ldc* cinq = malloc(sizeof(struct ldc));
    struct ldc* sept = malloc(sizeof(struct ldc));
    struct ldc* neuf = malloc(sizeof(struct ldc));
    trois->prev = neuf;
    trois->suiv = cinq;
    trois->numero = 3;
    cinq->prev = trois;
    cinq->suiv = sept;
    cinq->numero = 5;
    sept->prev = cinq;
    sept->suiv = neuf;
    sept->numero = 7;
    neuf->prev = sept;
    neuf->suiv = trois;
    neuf->numero = 9;
    return trois;
}

Test(insere_fin_vide, test1, .timeout = 5)
{
    struct ldc* l = create_empty_list();
    ldc_insere_fin(&l, 7);
    cr_assert(l != NULL);
    cr_expect(l->numero == 7);
    cr_expect(l->prev == l);
    cr_expect(l->suiv == l);
}

Test(insere_fin_singleton, test2, .timeout = 5)
{
    struct ldc* l = create_singleton_list();
    ldc_insere_fin(&l, 5);
    cr_assert(l != NULL);
    cr_expect(l->numero == 3);
    cr_assert(l->suiv != NULL);
    cr_assert(l->prev != NULL);
    cr_expect(l->suiv == l->prev);
    cr_expect(l->suiv->numero == 5);
    cr_expect(l->suiv->prev == l->suiv->suiv);
    cr_expect(l->suiv->prev == l);
}

Test(affiche_vide, test3, .timeout = 5)
{
    ldc_affiche(NULL);
}

Test(affiche_singleton, test4, .timeout = 5)
{
    struct ldc* singleton = create_singleton_list();
    ldc_affiche(singleton);
}

Test(affiche_preums, test5, .timeout = 5)
{
    struct ldc* preums = create_preums_list();
    ldc_affiche(preums);
}

Test(taille_vide, test6, .timeout = 5)
{
    cr_expect(ldc_taille(NULL) == 0);
}

Test(taille_singleton, test7, .timeout = 5)
{
    struct ldc* singleton = create_singleton_list();
    cr_expect(ldc_taille(singleton) == 1);
}

Test(taille_preums, test8, .timeout = 5)
{
    struct ldc* preums = create_preums_list();
    cr_expect(ldc_taille(preums) == 4);
}

Test(recupere_nieme, test9, .timeout = 5)
{
    struct ldc* preums = create_preums_list();
    cr_expect(ldc_recupere_nieme(preums->suiv, 0)->numero == 5);
    cr_expect(ldc_recupere_nieme(preums, 1)->numero == 5);
    cr_expect(ldc_recupere_nieme(preums, 2)->numero == 7);
    cr_expect(ldc_recupere_nieme(preums->suiv, 3)->numero == 3);
}

Test(supprime_singleton, test10, .timeout = 5)
{
    struct ldc* singleton = create_singleton_list();
    ldc_supprime(&singleton, singleton);
    cr_expect(singleton == NULL);
}

Test(supprime_tete, test11, .timeout = 5)
{
    struct ldc* preums = create_preums_list();
    ldc_supprime(&preums, preums);
    cr_expect(preums->numero == 5);
    cr_expect(preums->prev->numero == 9);
    cr_expect(preums->suiv->numero == 7);
}

Test(supprime_milieu, test12, .timeout = 5)
{
    struct ldc* preums = create_preums_list();
    ldc_supprime(&preums, preums->suiv);
    cr_expect(preums->numero == 3);
    cr_expect(preums->prev->numero == 9);
    cr_expect(preums->suiv->numero == 7);
    cr_expect(preums->suiv->prev == preums);
}

Test(supprime_fin, test12, .timeout = 5)
{
    struct ldc* preums = create_preums_list();
    ldc_supprime(&preums, preums->prev);
    cr_expect(preums->numero == 3);
    cr_expect(preums->prev->numero == 7);
    cr_expect(preums->prev->prev->numero == 5);
}


