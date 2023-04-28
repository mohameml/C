#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>

/*
    On décide de répéter l'exécution du bloc de code dont on veut mesurer
    le temps d'exécution un grand nombre de fois. Cela permet d'utiliser
    un outil de prise de temps à gros grain (comme gettimeofday(), qui compte
    à la granularité d'une microseconde) même quand on souhaite mesurer un
    traitement au temps d'exécution court (ici, de l'ordre de quelques nanosecondes
    pour certaines versions). Il suffira ensuite de diviser le temps obtenu
    par le nombre de répétitions pour obtenir une estimation du temps d'exécution
    du bloc de code étudié (représentant du coup la moyenne des temps obtenus).
*/
#define NTIMES 10000000

/*
    Le module de prise de temps définit une structure timeval, disposant de
    deux champs :
    - le nombre total de secondes écoulées tv_sec ;
    - le nombre de microsecondes écoulées depuis la dernière seconde tv_usec.

    Pour calculer le nombre total de microsecondes écoulées entre t1 et t2,
    on ramène le nombre de secondes en microsecondes en le multipliant
    par 1000000.
*/
static double elapsed_time(struct timeval t1,
                           struct timeval t2) {
    return (double)((t2.tv_sec - t1.tv_sec) * 1000000
           + (t2.tv_usec - t1.tv_usec));
}


/*
    Cette fonction lance la fonction compute_sum passée en paramètre
    (et oui, un pointeur de fonction!) ntimes fois et affiche son temps
    d'exécution moyen, ainsi que la chaine de caractères version_tag.

    Un pointeur de fonction en C s'écrit de cette façon :
    type_de_retour (*nom_du_pointeur_de_fonction)(type_des_paramètres);

    Par exemple, char *(*camion)(void) représente une fonction sans
    paramètre, qui retourne une chaine de caractères. Je ne sais pas ce qu'elle
    fait, mais je sais que je peux l'appeler en écrivant :
    char *pouetpouet = camion();

    Pour passer une fonction en paramètre d'une autre fonction, on utilise
    simplement son nom :
    repeat_and_time(hello, 10, "blabla");
    compilera à condition que hello soit une fonction de prototype :
    uint32_t hello(void);
*/
static void repeat_and_time(uint32_t (*compute_sum)(void),
                            uint32_t ntimes,
                            const char *version_tag) {
    struct timeval start, stop;
    /*
        Un appel à gettimeofday remplit la structure timeval passée en
        paramètre avec le nombre de secondes et de microsecondes
        écoulées depuis une certaine date (par défaut le 1er janvier 1970).
    */
    gettimeofday(&start, NULL);
    uint32_t sum = 0;
    for (unsigned times = 0; times < ntimes; times++) {
        sum = compute_sum();
    }
    gettimeofday(&stop, NULL);
    printf("Elapsed time for %s: %lfus\n",
            version_tag,
            elapsed_time(start, stop) / NTIMES);
    assert(sum == (uint32_t)-1);
}

int main(void)
{
    /*
        TODO: Définir une fonction qui calcule la somme des 32 premières
        puissances de 2 et l'évaluer à l'aide de repeat_and_time().
    */

    return EXIT_SUCCESS;
}
