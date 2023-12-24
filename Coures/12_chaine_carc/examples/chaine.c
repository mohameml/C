#include <stdio.h>
#include <string.h>


int main(void)
{

    printf("---------------Decleration et affichage  d'une chaine -------------\n");
    signed char mot[]="bonjour sidi ";

    printf("%s\n",mot);

    // si on veut recpere des chaines a partir des utilisaateures 

    printf("----------Récuperation d'une chiane ------------------\n");

    signed char prenom[25];

    printf("votre prenom svp ");
    scanf("%s",prenom);
    printf("Votre prenom est ---> %s\n",prenom);


    // on veut itiliser une biblio des chaines des car......

    printf("---------la fonction strcpy : ----------------\n");

    strcpy(mot,prenom);

    printf("donc bah le nouveau Mots apres la copie est : %s\n",mot);


    // longeure d'une chaine 

    printf("----------LA fonction strlen(): ---------------\n");

    printf("En faite la taille de votre prenom est %zu\n",strlen(mot));

    // on veut utilise mnt la fonction strcmp : qui compare deux mots au sens lexicographique 




    printf("-----------la fonction strcmp(): --------------\n");


    char m1[]="bonjour";
    char m2[]="coucou";
    int test = strcmp(m1,m2);

    if(test==0)
      printf("%s==%s",m1,m2);
    else if(test<0)
      printf("%s<%s\n",m1,m2);
    
    else 
       printf("%s>%s",m1,m2);


    // la fonction strcat(): qui permet des fusioner deux chaine des carecteres 

    printf("-------la fonction strcat()-------------\n");

    char mot1[]="Nebil ";
    char mot2[]="Mohamed Lemine ";

    printf("%s\n",strcat(mot1,mot2));

    // la fonction strstr(): qui peremet de rechercher une chaie dans un autre chaine 

    printf("-----------------la fonction strstr()---------------------------------------\n");

    char mot3[]="bil ";

    if(strstr(mot1,mot3) != NULL)
      printf("Le mot est bien treouver \n");
    else 
      printf("Le mot n'est pas trouver \n");
 
    
    // la fonction : strchr(texte,c) qui cherche le 1ere occurence  du c dans texte et retourne une chaine 

    printf("------------la fonction strchr()------------------\n");
    char texte[]="yin-yang";
    char c ='-';
    char *resultat = strchr(texte, c);
    printf("%s\n",resultat);
    

    // la fonction sprintf() : qui permet d'ercrire dans une chaine 
    printf("-----------la fonction sprintf()-----------------------\n");

    char txt[256];
    sprintf(txt,"Nebil");

    printf("%s\n",txt);


    return 0 ;
}