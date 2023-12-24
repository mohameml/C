#include <stdio.h>



// Prototype de la fonction qui calcule le carré d'un entier

int carre( int n );

int main(void) {
  int x=8;
  printf("%d*%d = %d\n", x, x, carre(x));
  return 0;
}

// Implémentation de la fonction qui calcule le carré d'un entier

// COMPLETER ICI

int carre(int n )
{
    return n*n;
}