/******************************************************
 * Copyright Grégory Mounié 2018-2022                 *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <sys/mman.h>
#include <assert.h>
#include <stdint.h>
#include "mem.h"
#include "mem_internals.h"

unsigned long knuth_mmix_one_round(unsigned long in)
{
    return in * 6364136223846793005UL % 1442695040888963407UL;
}

void *mark_memarea_and_get_user_ptr(void *ptr, unsigned long size, MemKind k)
{
    unsigned long* cp_ptr = (unsigned long*)ptr ;

    cp_ptr[0] = size ;
    
    // calcul de la valeur magique :
    
    unsigned long magic =  knuth_mmix_one_round((unsigned long)cp_ptr);
    
    // conservons les bits de magic sauf les derniers bits
    unsigned long masq_magic = ~(0b11UL);
    unsigned long faible_bits = k;

    magic = (magic & masq_magic) | faible_bits ;

    

    
    cp_ptr[1] = magic ;


    int  taille = 4*8 ;
    int alpha = (size - taille )/8 +2;
    

    cp_ptr[alpha] = magic ;

    cp_ptr[alpha+1] = size ;
    
    // retournons l'adresse ptr de la zone mémoire de l'utilisateur

    ptr+=16;

    return ptr;

}

Alloc mark_check_and_get_alloc(void *ptr)
{

    Alloc a = {};

    //pour récuperer la valeur magic
    ptr-=8;
    unsigned long magic = *(unsigned long*)ptr;

    // pour récupperer la taille
    ptr -=8;
    a.size = *((unsigned long*)ptr);

    // récupere ptr
    a.ptr = ptr;

    // récuperer  kind
    int k = magic & 0b11UL;
    a.kind = k ;



    return a;
}


unsigned long mem_realloc_small() 
{
    assert(arena.chunkpool == 0);
    unsigned long size = (FIRST_ALLOC_SMALL << arena.small_next_exponant);
    arena.chunkpool = mmap(0,
			   size,
			   PROT_READ | PROT_WRITE | PROT_EXEC,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   -1,
			   0);

    if (arena.chunkpool == MAP_FAILED)
	handle_fatalError("small realloc");
    arena.small_next_exponant++;
    return size;
}

unsigned long mem_realloc_medium() 
{
    uint32_t indice = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant;
    assert(arena.TZL[indice] == 0);
    
    unsigned long size = (FIRST_ALLOC_MEDIUM << arena.medium_next_exponant);
    assert( size == (1UL << indice));
    
    arena.TZL[indice] = mmap(0,
			     size*2, // twice the size to allign
			     PROT_READ | PROT_WRITE | PROT_EXEC,
			     MAP_PRIVATE | MAP_ANONYMOUS,
			     -1,
			     0);
    if (arena.TZL[indice] == MAP_FAILED)
	handle_fatalError("medium realloc");
    
    // align allocation to a multiple of the size
    // for buddy algo
    arena.TZL[indice] += (size - (((intptr_t)arena.TZL[indice]) % size));
    arena.medium_next_exponant++;
    
    return size; // lie on allocation size, but never free
}


// used for test in buddy algo
unsigned int nb_TZL_entries() {
    int nb = 0;
    
    for(int i=0; i < TZL_SIZE; i++)
	if ( arena.TZL[i] )
	    nb ++;

    return nb;
}
