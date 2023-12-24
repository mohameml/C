/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <stdint.h>
#include <assert.h>
#include "mem.h"
#include "mem_internals.h"

unsigned int puiss2(unsigned long size) {

    unsigned int p=0;
    size = size -1; // allocation start in 0
    while(size) 
    {  // get the largest bit
	    p++;
	    size >>= 1;
    }
    if(size > (1 << p))
	    p++;
    
    return p;
}


void* emalloc_medium(unsigned long size)
{
    assert(size < LARGEALLOC);
    assert(size > SMALLALLOC);


    unsigned long taille_size = size + 32 ;
    unsigned int indice = puiss2(taille_size); //  l’indice de la TZL contenant la bonne taille 


    if(arena.medium_next_exponant==0)
    {
        // c'est la premier fois qu'on applelle ctte fonction il faut applere la fonction realloce_meduim :
        mem_realloc_medium();
    }
    


    if(arena.TZL[indice]!=NULL)
    {
        void* elem = arena.TZL[indice];

        // on marque que arena.TZL[inidce] est allouée mnt :

        arena.TZL[indice]=NULL ;



        return mark_memarea_and_get_user_ptr(elem, taille_size ,MEDIUM_KIND);
    }
    else
    {





        if( indice <  FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant - 1 )
        {

            
            int nb_parcour_1 = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant - 1 - indice ;


            // l'objectif est  de chercher le plus petite inidce i tq arean.TZL[i]!=NULL

            int indice_min = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant - 1;

            for(int i = 0 ; i < nb_parcour_1 ; i++)
            {
                if(arena.TZL[FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant - 1 - i]!=NULL && i < indice_min)
                {
                    indice_min = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant - 1 - i ;
                }
            }


            // 

            int nb_parcour_2 = indice_min - indice ;

            for(int i =1 ; i <= nb_parcour_2 ; i++)
            {
                arena.TZL[indice_min - i] = arena.TZL[indice_min] + (1<<indice_min)/(1<<i);
            }


            

            void* elem = arena.TZL[indice_min];

            arena.TZL[indice_min] = NULL ;

            return mark_memarea_and_get_user_ptr(elem, taille_size ,MEDIUM_KIND);
        }
        else
        {
            // si indice >  FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant - 1


            
            int diff = indice - FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant -1  ;

            if(diff==0)
            {
                mem_realloc_medium();
                arena.TZL[indice]= arena.TZL[indice +1] + (1<<(indice+1))/2;
                void* elem = arena.TZL[indice];

                return  mark_memarea_and_get_user_ptr(elem, taille_size ,MEDIUM_KIND);

            }
            else 
            {

                for(int i = 0 ; i<diff ; i++)
                {
                    
                    mem_realloc_medium();

                }

                void* elem = arena.TZL[indice];

                return mark_memarea_and_get_user_ptr(elem, taille_size ,MEDIUM_KIND);   

            }


            


            
        }
    }

}


void efree_medium(Alloc a) {

    unsigned long  adrr_compagnon_int = (unsigned long) a.ptr ^ a.size;
    void * adrr_compagnon = (void*) adrr_compagnon_int;

    unsigned long taille_size = a.size  ;
    unsigned int indice_TZL = puiss2(taille_size);
    
    if(arena.TZL[indice_TZL] == NULL) //il n'est pas présent dans la liste
    {
        arena.TZL[indice_TZL] = a.ptr;
        
    }else if(arena.TZL[indice_TZL] == adrr_compagnon )
    {                          // il est présent dans la liste
        

        arena.TZL[indice_TZL] = NULL;
        unsigned int next_indice_TZL = indice_TZL+1;
       

        while(arena.TZL[next_indice_TZL] != NULL){

            // unsigned long nv_size = (unsigned long)1<<(unsigned long)next_indice_TZL;

            // adrr_compagnon_int = (unsigned long) adrr_compagnon_int ^ nv_size;
            // adrr_compagnon = (void*) adrr_compagnon_int;

            arena.TZL[next_indice_TZL] = NULL;

            next_indice_TZL++;
        }
        arena.TZL[next_indice_TZL] = a.ptr;
        
    }
    a.ptr=NULL;
}






