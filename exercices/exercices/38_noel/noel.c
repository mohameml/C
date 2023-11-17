#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static bool noel(bool boule, bool guirlande, bool sapin, bool lapin)
{
    // A compléter
}

int main(void)
{
    if ( noel(false,false,false,false)) goto Cestpasgagne;
    if ( noel(true ,false,false,false)) goto Cestpasgagne;
    if ( noel(false,true ,false,false)) goto Cestpasgagne;
    if ( noel(true ,true ,false,false)) goto Cestpasgagne;
    if ( noel(false,false,true ,false)) goto Cestpasgagne;
    if (!noel(true ,false,true ,false)) goto Cestpasgagne;
    if (!noel(false,true ,true ,false)) goto Cestpasgagne;
    if (!noel(true ,true ,true ,false)) goto Cestpasgagne;
    if ( noel(false,false,false,true )) goto Cestpasgagne;
    if ( noel(true ,false,false,true )) goto Cestpasgagne;
    if ( noel(false,true ,false,true )) goto Cestpasgagne;
    if ( noel(true ,true ,false,true )) goto Cestpasgagne;
    if ( noel(false,false,true ,true )) goto Cestpasgagne;
    if ( noel(true ,false,true ,true )) goto Cestpasgagne;
    if ( noel(false,true ,true ,true )) goto Cestpasgagne;
    if ( noel(true ,true ,true ,true )) goto Cestpasgagne;
    printf("Joyeux Noel\n");
    return EXIT_SUCCESS;
    /*
        Note : L'utilisation de goto en C est généralement à proscrire.
        Tracer des erreurs est une des rares exceptions à son usage.
    */

Cestpasgagne:
    printf("C'est pas gagné !\n");
    return EXIT_FAILURE;
}
