#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char lettre = 'L';

    if (isupper(lettre)) {
        printf("La lettre %c est une majuscule.\n", lettre);
    } else {
        printf("La lettre %c est une minuscule.\n", lettre);
    }

    return EXIT_SUCCESS;
}
