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
}

/* Affiche le rapport de vitesse entre 2 processus */
void print_speed(char *processus1, char *processus2, struct timespec timer1, struct timespec timer2)
{
    /*  A compléter, exemple d'affichage désiré :
	"copytab2 est allé 9.45 fois plus vite que copytab1" */
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
