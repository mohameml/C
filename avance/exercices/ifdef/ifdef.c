#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const char *blabla;

#ifdef V1
    blabla = "Félicitations, vous avez compilé la version 1 de ce programme!\n";
#elif defined(V2)
    blabla = "Félicitations, vous avez compilé la version 2 de ce programme!\n";
#else
    blabla = "Raté! Vous n'avez défini ni V1 ni V2 à la compilation.\n";
#endif

    printf("%s\n", blabla);
    printf("J'ai tout compris, en fait!\n");
    return EXIT_SUCCESS;
}
