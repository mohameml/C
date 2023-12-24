/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <assert.h>
#include "mem.h"
#include "mem_internals.h"

void* emalloc_small(unsigned long size)
{
    if(arena.chunkpool!=NULL)
    {
        void* elem_demandé = arena.chunkpool;

        // arena.chunkpool = arena.chunkpool + 96;
        
        *((void**)arena.chunkpool) =  arena.chunkpool + 96;

        return mark_memarea_and_get_user_ptr(elem_demandé, CHUNKSIZE, SMALL_KIND);

    }
    else
    {
        unsigned long taille = mem_realloc_small();
        int nbBloc = taille / CHUNKSIZE;

        void*  tete = arena.chunkpool ;  
        void* current_elem = tete; 

        for(int i=0 ; i< nbBloc -1 ;i++)
        {
            void* next_elem =  current_elem + 96  ; 
            *(void**)current_elem = next_elem;
            current_elem = next_elem ;
        }



        arena.chunkpool = *(void **)arena.chunkpool;    

        return mark_memarea_and_get_user_ptr(tete, CHUNKSIZE, SMALL_KIND);

        
    }


    
}

void efree_small(Alloc a) {
    

    //  replace le chunk, décrit dans la variable a , en tête de la liste chainée.

    *((void**)a.ptr) = arena.chunkpool ;
    *((void**)arena.chunkpool) = a.ptr ;  
    


}
