#include <stdio.h>


/*
Écrire le code qui permet d’afficher un carré de n lettres de côté contenant les lettres de l’alphabet.

La première ligne commence par la lettre A
La deuxième ligne commence par la lettre B
La troisième ligne commence par la lettre C
et ainsi de suite.
*/

// rq : char lettre='A' alose lettre +1 ---> B ....etc 

int main(void) {
  int l,c,n=6;

  // COMPLETER ICI

  for(l=0;l<n;l++)
  {
    for(c=0;c<n;c++)
    {
        printf("%c",'A'+l+c);
        
    }
    printf("\n");
  }




  return 0;
}