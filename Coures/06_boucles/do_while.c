#include <stdio.h>

int main(void) {

  float note;

  // Saisie de la note entre 0 et 20
  do{
    printf("saisie une note svp : ");
    scanf("%f",&note);


  }
  while(note<0 || note>20);

  // Affichage de la note
  printf ("La note est %.1f.\n", note);
  return 0;
}