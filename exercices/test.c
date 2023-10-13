#include <stdio.h>

#define TZL_SIZE 48 

typedef struct mem
{
    int taille ;
    void* TZL[TZL_SIZE];
}mem;


// une varibale globale 

mem M1 = {};


int main(void)
{

    printf("----- Test de M1 ------- \n");

    printf("taille de M1 est %d \n",M1.taille);

    for(int i=0 ; i<TZL_SIZE;i++)
    {
        printf("l'élmeent %d de TZL est %p \n",i,M1.TZL[i]);
    }



    return 0 ;
}

typedef struct _MemArena {
    void *chunkpool;
    void *TZL[TZL_SIZE];
    int small_next_exponant;
    int medium_next_exponant;
} MemArena






