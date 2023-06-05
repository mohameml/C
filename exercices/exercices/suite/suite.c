/*
    Enoncé :

    Cet exercice est un exercice de debug. Le programme suivant comporte
    trois problèmes, à vous de les trouver en utilisant l'outil approprié,
    puis de les corriger.

    Ce programme permet de construire la suite croissante des N premiers
    entiers x tels x = 2^i, pour i allant de 1 à N.

    On utilise l'allocation dynamique pour allouer l'espace mémoire qui
    permettra de stocker les termes de la suite, ce qui nous permet à
    notre implémentation de gérer n'importe quelle taille de suite.

    Compétences : 20,35,36,91,92,94,96,107,111
    Difficulté : 3
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* La structure suite modélise notre suite de puissances de deux. */
struct suite
{
    /* Un tableau de puissances de deux. */
    uint32_t *terme;

    /* Le nombre de termes de la suite. */
    size_t taille;
};

/*
    Alloue et initialise une nouvelle suite dont la taille est passée
    en paramètre. La fonction retourne un pointeur sur la suite
    nouvellement crééé.
*/
static struct suite *init_suite(size_t taille)
{
    /*
        On souhaite créer un objet dont la durée de vie dépasse celle
        de la fonction init_suite. On utilise donc l'allocation
        dynamique : l'objet perdurera en mémoire tant qu'on n'aura pas
        explicitement libéré la mémoire qui lui est associé.
    */
    struct suite *ret = malloc(sizeof(struct suite));

    /*
        La ligne suivante indique : "Je suis certain que ret est
        différent de NULL!". Si ce n'est pas le cas, le programme
        s'arrête et un message explicite s'affiche sur le terminal
        (man assert). Si on voulait en savoir plus sur l'erreur qui
        s'est produite, on pourrait utiliser perror (man malloc, man
        perror).
    */
    assert(ret != NULL);

    ret->taille = taille;
    /*
        Même chose pour le tableau de termes : on souhaite qu'il soit
        toujours accessible quand cette fonction aura retourné.
    */
    ret->terme = malloc(taille * sizeof(uint32_t));
    assert(ret->terme != NULL);

    for (size_t i = 1; i <= taille; i++) {
        /*
            On construit la suite des taille premiers entiers x tels
            que x = 2^i.
        */
        ret->terme[i] = 1 << i;
    }

    /*
        On retourne simplement l'adresse en mémoire où retrouver la
        suite allouée dynamiquement.
    */
    return ret;
}


static void print_suite(struct suite *s)
{
    printf("La suite comporte %zu termes:\n", s->taille);
    for (size_t i = 1; i <= s->taille; i++) {
        printf("%u ", s->terme[i]);
    }
    printf("\n");
}

int main(void)
{
    /* On créé une suite de 10 termes. */
    struct suite *s = init_suite(10);

    /* On l'affiche! */
    print_suite(s);

    return EXIT_SUCCESS;
}
