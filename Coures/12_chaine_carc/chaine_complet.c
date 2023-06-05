
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>


bool lire_ligne(char *chaine, size_t max)
{
    size_t i;

    for (i = 0; i < max - 1; ++i)
    {
        char c;

        if (scanf("%c", &c) != 1)
            return false;
        else if (c == '\n')
            break;

        chaine[i] = c;
    }

    chaine[i] = '\0';
    return true;
}


int main(void)
{
    char chaine[255];

    printf("Quel est votre prénom ? ");

    if (lire_ligne(chaine, sizeof chaine))
        printf("Bien le bonjour %s !\n", chaine);

    return 0;
}