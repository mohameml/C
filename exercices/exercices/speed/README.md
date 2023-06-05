# Enoncé

Au menu de cet exercice: les fonctions de manipulation de la mémoire.
Et au passage, une compétence qui n'est pas dans la carte : la gestion
du temps réel appliquée au calcul de la durée d'exécution des
processus.

Nota Bene : option `-std=gnu99` au lieu de `-std=c99` pour pouvoir
utiliser la fonction `clock_gettime` permettant d'obtenir une
précision de l'ordre de la nanoseconde gnu99 = c99 + extensions gnu

Spécifications `clock_gettime` :

```c
int clock_gettime(clockid_t clk_id, struct timespec *tp);

struct timespec {
	  time_t   tv_sec;        // seconds
	  long     tv_nsec;       // nanoseconds
};

// clk_id : CLOCK_REALTIME, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID
```


NOTA BENE : La fonction standard `clock()` de la librairie `time.h`
est théoriquement adaptée à ce genre de calcul de temps mais
fonctionne en réalité très mal, en particulier sous linux.

Le point de départ pour cet exercice (squelette de code, énoncé) se
trouve dans `exercices/avance/speed/`.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* Regardez la documentation des fonctions `memcpy` et `memset`

</details>

# Compétences

* Conditions combinées avec opérateurs logiques
* Copie de zones mémoire

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
# std=gnu99 : gnu99 = c99 + gnu extensions. Utilisé ici pour avoir accès aux fonctions de temps réel avec une précision de nanoseconde (clock_gettime,...)
CFLAGS=-g -std=gnu99 -Wall -Wextra
# Le librairie nécessaire pour utiliser clock_gettime est : librt
LDFLAGS=-lrt

speed: speed.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean :
	rm -f *.o speed

```

#### Corrigé du fichier speed.c

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE 100000

struct ordi {
    char nom[20];
    uint16_t memoire;   // Taille mémoire en Go
    uint16_t disque;    // Taille disque en Go
    float vitesse;      // Vitesse processeur en Ghz
};

/* Copie de structure - méthode 1 - code complet fourni */
void copyordi1(struct ordi *dst, struct ordi src)
{
    strcpy(dst->nom, src.nom);
    dst->memoire = src.memoire;
    dst->disque = src.disque;
    dst->vitesse = src.vitesse;
}

/* Copie de structure - méthode 2 */
void copyordi2(struct ordi *dst, struct ordi src)
{
    /* A compléter en une seule instruction */
    memcpy(dst, &src, sizeof(struct ordi));
}

/* Mise à 0 d'un tableau : méthode 1 - code complet fourni */
void fillzero1(double *tab, uint32_t length)
{
    for (uint32_t i=0; i< length; i++) {
	tab[i] = 0.;
    }
}

/* Mise à 0 d'un tableau : méthode 2 */
void fillzero2(double *tab, uint32_t length)
{
    /* A compléter sans aucune boucle et en une seule instruction */
    memset(tab, 0, length * sizeof(double));
}

/* Copie de tableau : méthode 1 - code complet fourni */
void copytab1(double *tab1, double *tab2, uint32_t length)
{
    for (uint32_t i=0; i< length; i++) {
	tab1[i] = tab2[i];
    }
}

/* Copie de tableau : méthode 2 */
void copytab2(double *tab1, double *tab2, uint32_t length)
{
    /* A compléter sans aucune boucle et en une seule instruction */
    memcpy(tab2, tab1, length * sizeof(double));
}

/* Affichage des 5 premières valeurs du tableau : code complet fourni */
void print_tab(char *nomtab, double *tab, uint32_t length)
{
    for (uint32_t i = 0; i < ((length >= 5) ? 5 : length); i++) {
	printf("%s[%u] = %lf\n", nomtab, i, tab[i]);
    }
}

/* Affiche et retourne la durée d'un processus dont le nom est passé en paramètre ainsi que les temps de début et de fin */
struct timespec print_duration(char *processus, struct timespec start, struct timespec end)
{
    /*  A compléter :
	Calculer la durée entre le temps end et le temps start
	Le résultat est à mettre dans une structure struct timespec
	Ce résultat sera retourné par la fonction
	Attention au cas où où end.tv_nsec est inférieur à start.tv_nsec
	La fonction affichera également le résultat selon l'exemple suivant :
	"copytab1 a été exécuté en 0 secondes 71458 nanosecondes"
	*/
    struct timespec diff;
    if ((end.tv_nsec-start.tv_nsec)<0) {
	diff.tv_sec = end.tv_sec-start.tv_sec-1;
	diff.tv_nsec = 1e9+end.tv_nsec-start.tv_nsec;
    } else {
	diff.tv_sec = end.tv_sec-start.tv_sec;
	diff.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    printf("%s a été exécuté en %ld secondes %ld nanosecondes\n", processus, diff.tv_sec, diff.tv_nsec);
    return diff;
}

/* Affiche le rapport de vitesse entre 2 processus */
void print_speed(char *processus1, char *processus2, struct timespec timer1, struct timespec timer2)
{
    /*  A compléter, exemple d'affichage désiré :
	"copytab2 est allé 9.45 fois plus vite que copytab1" */
    if (timer1.tv_sec > timer2.tv_sec || (timer1.tv_sec == timer2.tv_sec && timer1.tv_nsec > timer2.tv_nsec)) {
	printf("%s est allé %1.2lf fois plus vite que %s\n", processus2, ((double)timer1.tv_sec * 1E9 + timer1.tv_nsec) / ((double)timer2.tv_sec * 1E9 + timer2.tv_nsec), processus1);
    } else {
	printf("%s est allé %1.2lf fois plus vite que %s\n", processus1, ((double)timer2.tv_sec * 1E9 + timer2.tv_nsec) / ((double)timer1.tv_sec * 1E9 + timer1.tv_nsec), processus2);
    }
}

int main(void)
{
    struct timespec start, end, timer1, timer2;

    struct ordi o1, o2;
    strcpy(o1.nom, "Asus272");
    o1.memoire = 8;
    o1.disque = 1000;
    o1.vitesse = 2.4;

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
    copyordi1(&o2, o1);
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &end);
    timer1 = print_duration("copyordi1", start, end);

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
    copyordi2(&o2, o1);
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &end);
    timer2 = print_duration("copyordi2", start, end);

    print_speed("copyordi1", "copyordi2", timer1, timer2);

    double tab1[SIZE], tab2[SIZE];
    for (uint32_t i=0; i< SIZE; i++) {
	tab1[i] = i * 3.14159;
    }

    print_tab("tab1", tab1, SIZE);

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
    fillzero1(tab2, SIZE);
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &end);
    timer1 = print_duration("fillzero1", start, end);

    print_tab("tab2", tab2, SIZE);

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
    fillzero2(tab2, SIZE);
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &end);
    timer2 = print_duration("fillzero2", start, end);

    print_tab("tab2", tab2, SIZE);

    print_speed("fillzero1", "fillzero2", timer1, timer2);

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
    copytab1(tab2, tab1, SIZE);
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &end);
    timer1 = print_duration("copytab1", start, end);

    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &start);
    copytab2(tab2, tab1, SIZE);
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &end);
    timer2 = print_duration("copytab2", start, end);

    print_tab("tab2", tab2, SIZE);

    print_speed("copytab2", "copytab1", timer2, timer1);
    print_speed("copytab1", "copytab2", timer1, timer2);

    return EXIT_SUCCESS;
}

```


</details>
