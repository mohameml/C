#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void afficher_papous(bool est_papa, bool a_poux)
{
}

int main(void)
{
    printf("Chez les papous...\n");
    afficher_papous(true, true);
    afficher_papous(true, false);
    afficher_papous(false, true);
    afficher_papous(false, false);

    return EXIT_SUCCESS;
}
