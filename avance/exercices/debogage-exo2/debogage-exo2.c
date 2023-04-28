#include <stdio.h>

#define VAL 42
#define ZERO VAL-42

int main()
{
    int zero, la_tete_a_toto, i, j, k;
    printf("VAL=%d\n", VAL);
    printf("ZERO=%d\n", ZERO);
    zero = ZERO;					/* 0 */
    la_tete_a_toto = zero * ZERO;	/* 0 */
    i = VAL + VAL;					/* 84 */
    j = la_tete_a_toto + i;			/* 84 */
    k = zero + la_tete_a_toto + j;	/* 84 */
    printf("La, normalement, on devrait avoir 84 : %d\n", k);
    printf("Enfin, en principe ...\n");
    return 0;
}

