#include <stdio.h>
#include <stdbool.h>
#define TAILLE 1000

struct elem
{
    int val ;
    struct elem* next ;
};


static unsigned char memeoire_pool_elme[sizeof(struct elem)*TAILLE];
static bool elemes_utilisés[TAILLE];


void init_elems()
{
    for(int i=0 ; i<TAILLE ; i++)
    {
        elemes_utilisés[i]=false ;
    }
}


struct elem* alloc_elem()
{
    for(int i=0 ; i<TAILLE ; i++)
    {
        if(elemes_utilisés[i]==false)
        {
            elemes_utilisés[i]=true ;
            return (struct elem*)(memeoire_pool_elme +i*sizeof(struct elem));
        }
    }

    // le pool est peline :
    printf("le pool est pleine ..!!!! \n");
    return NULL ;
}


void gc_elems(int nbheads , struct elem **heads)
{
    init_elems();

    for(int i=0 ; i<nbheads ; i++)
    {
        struct elem* tete = heads[i];

        while(tete!=NULL)
        {
            int indice = ((unsigned char* )tete - memeoire_pool_elme )/sizeof(struct elem);

            if(indice>=0 && indice<TAILLE)
            {
                elemes_utilisés[indice]=true ;
            }
            tete=tete->next;
        }
    
    }
}

void affichage_liste(struct elem  *liste) {
  /**
     Votre code est à mettre ici !
  */

 if(liste==NULL)
 {
  printf("votre liste est vide \n");
 }
 else
 {
    struct elem const * ptr = liste ;
    while(ptr->next!=NULL)
    {
      printf("%d-> ",ptr->val);

      ptr = ptr->next;
    }

    printf("%d \n",ptr->val);
 }

}



int main(void)
{
    // Test simple de 4 élmemts de struct elme :

    struct elem *e1 = alloc_elem() ;
    struct elem *e2 = alloc_elem();
    struct elem *e3 = alloc_elem();
    struct elem *e4 = alloc_elem();

    e1->val = 1;
    e2->val = 2;
    e3->val =3 ;
    e4->val = 4 ;
    
    e1->next = e2 ;
    e2->next = e3 ;
    e3->next = e4 ;
    e4->next = NULL ;

    affichage_liste(e1);

    // affichage de elmes utilises :
    for(int i=0 ; i<10;i++)
    {
        printf("%d \n", elemes_utilisés[i]);
    }

    for(int i=0 ;i<TAILLE;i++ )
    {
        struct elem* e5 = alloc_elem();
    }

    printf("avant la ramasse miette \n");
    for(int i=0 ; i<10;i++)
    {
        printf("%d \n", elemes_utilisés[i]);
    }

    gc_elems(1,&e1);

    printf("Apres la ramasse miette \n");
    for(int i=0 ; i<10;i++)
    {
        printf("%d \n", elemes_utilisés[i]);
    }

    

    return 0 ;
}