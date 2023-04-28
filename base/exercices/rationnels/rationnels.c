#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/*
    On définit le type "struct rationnel" contenant deux champs:
    un numérateur et un dénominateur.
*/
struct rationnel
{
    /* numérateur */
    uint32_t n;

    /* dénominateur */
    uint32_t d;
};

/* Retourne la valeur réelle associée au rationnel r. */
static float valeur_rationnel(struct rationnel r)
{
    float ret;
    return ret;
}

/*
    Effectue la somme des rationnels r1 et r2 dans un nouveau rationnel
    r, puis retourne la valeur réelle qui lui est associée.
*/
static float somme_puis_convertit(struct rationnel r1,
                                  struct rationnel r2)
{
    float ret = 0.0;
    return ret;
}

/*
    Retourne la somme des valeurs réelles associées aux rationnels r1
    et r2.
*/
static float convertit_puis_somme(struct rationnel r1,
                                  struct rationnel r2)
{
    float ret = 0.0;
    return ret;
}

int main(void)
{
    struct rationnel r1 = { 1, 7 };
    struct rationnel r2 = { 3, 4 };

    printf("%f est-il égal à %f?\n",
            somme_puis_convertit(r1, r2),
            convertit_puis_somme(r1, r2));

    return EXIT_SUCCESS;
}
