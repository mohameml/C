#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define MAX 12 /* taille max d'une allocation = 2^11 = 2048. */

/* Structure de données représentant une zone mémoire. */
struct data{
    /* L'adresse du début de la zone mémoire. */
    void *base;

    /* Sa taille, en octets. */
    size_t size;

    /* L'adresse de la prochaine zone mémoire disponible de même
     * taille (liste simplement chainée). */
    struct data *next;
};


/* Alloue et initialise à zéro la table passée en paramètre. La taille
 * de cette table est définie par la constante préprocesseur MAX. */
static void create_table(struct data ***table)
{
}

/* Libère la table passée en paramètre, de taille MAX. Pour chacune
 * des entrées de la table, libère aussi les zones mémoires
 * disponibles, si elles existent. */
static void destroy_table(struct data **table)
{
}

/*
   Alloue une nouvelle zone mémoire de taille size.
   Si il existe une zone mémoire disponible de taille size dans la table, on l'utilise.
   Sinon, on effectue une "vraie" allocation, via l'appel système malloc.

   Cett fonction arrête le programme de manière brutale (assert) si la
   taille passée en paramètre n'est pas une puissance de 2, ou dépasse MAX.
 */
static struct data *allocate(struct data **table, size_t size)
{
    struct data *ret = NULL;
    return ret;
}

/*
   Libère la zone mémoire d passée en paramètre.  Cette fonction
   n'appelle pas free : la zone mémoire libérée est chainée aux autres
   zones mémoires de même taille de la table.
 */
static void deallocate(struct data **table, struct data *d)
{
}

static void test(void)
{
    struct data **table = NULL;
    printf("On cree la table des zones mémoire.\n");
    create_table(&table);

    struct data *data1 = allocate(table, 128);
    void *data1_addr = data1->base;
    printf("Nouvelle zone mémoire de taille 128 allouée à l'adresse %p.\n", data1_addr);

    deallocate(table, data1);
    printf("La zone mémoire %p a été libérée, elle est donc disponible pour une allocation future.\n",
	    data1_addr);

    struct data *data2 = allocate(table, 128);
    void *data2_addr = data2->base;
    printf("Nouvelle zone mémoire de taille 128 allouée à l'adresse %p.\n", data2_addr);
    if (data1_addr == data2_addr) {
	printf("Super! On a bien réutilisé la zone mémoire libérée précédemment!\n");
    } else {
	printf("Argh... On aurait dû réutiliser de la mémoire, et on a fait malloc à la place!\n");
    }

    struct data *data3 = allocate(table, 128);
    printf("Nouvelle zone mémoire de taille 128 allouée à l'adresse %p.\n", data3->base);

    deallocate(table, data2);
    printf("La zone mémoire %p a été libérée, elle est donc disponible pour une allocation future.\n",
	    data2->base);

    deallocate(table, data3);
    printf("La zone mémoire %p a été libérée, elle est donc disponible pour une allocation future.\n",
	    data3->base);

    printf("On détruit la table des zones mémoire.\n");
    destroy_table(table);
}


int main(void)
{
    /* Vous pourrez appeler la fonction test() qui teste le bon
     * fonctionnement de l'allocateur, dès que vous aurez implémenté
     * l'exercice. */
    return EXIT_SUCCESS;
}
