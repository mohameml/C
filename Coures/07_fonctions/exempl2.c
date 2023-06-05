#include <stdio.h>

/*

Ecrire une fonction moyenne() qui retourne la moyenne de trois nombres flottants. 
Tester votre fonction avec un programme principal qui demande à l'utilisateur de saisir trois notes 
avant d'en afficher la moyenne. La fonction moyenne() ne doit rien afficher, 
mais retourner le résultat du calcul au programme principal.

*/
int moyenne( int n1, int n2 , int n3); // pertotoype


int main(void)
{
    int n1=0;
    int n2=0;
    int n3=0;
    printf("saisie le nb_1 :");
    scanf("%d",&n1);
    printf("saisie le nb_2 :");
    scanf("%d",&n2);
    printf("saisie le nb_3 :");
    scanf("%d",&n3);

    int moy ;
    moy = moyenne(n1,n2,n3);

    // Affichage :
    printf("-----------------------------\n");
    printf("La moyenne est %d \n",moy);


}

int moyenne( int n1, int n2 , int n3)
{
    return (n1 + n2 +n3)/3 ;
}