#include "Needleman-Wunsch-recPD.h"
#include "Needleman-Wunsch-recmemo.h"
#include <stdio.h>  
#include <stdlib.h>
#include <stdint.h>
#include <string.h> /* for strchr */
#include "characters_to_base.h" /* mapping from char to base */


#define NOT_YET_COMPUTED -1L 
static size_t S;


/** \struct NW_MemoContext
 * \brief data for memoization of recursive Needleman-Wunsch algorithm 
*/
struct NW_MemoContext 
{
    char *X ; /*!< the longest genetic sequences */
    char *Y ; /*!< the shortest genetic sequences */
    size_t M; /*!< length of X */
    size_t N; /*!< length of Y,  N <= M */
    long *memo; /*!< memoization table to store memo[0..M][0..N] (including stopping conditions phi(M,j) and phi(i,N) */
    long *strip;/*pour le cache aware*/
} ;

/********************************Methode iterative*****************************/
static long EditDistance_NW_PD(struct NW_MemoContext *c, size_t i, size_t j){
    //long memo[c->N + 1];
    c->memo[c->N] = 0;
    //char Xi = c->X[i];
    //char Yj = c->Y[j];
    for (size_t l = c->N - 1; (int64_t) l >= (int64_t)j; l--){
        char Yl = c->Y[l];
        c->memo[l] = (isBase(Yl) ? INSERTION_COST: 0) + c->memo[l + 1];
    }
    for (size_t k = c->M -1; (int64_t) k >= (int64_t)i; k--){
        char Xk = c->X[k] ;
        long res = c->memo[c->N];
        c->memo[c->N] = (isBase(Xk) ? INSERTION_COST : 0) + c->memo[c->N] ;
        for (size_t l = c->N - 1; (int64_t) l >= (int64_t)j; l--){
            char Yl = c->Y[l];
            /*if (l == c->N) /* Reach end of Y but not end of X *
            {  c->memo[k][l] = (isBase(Xk) ? INSERTION_COST : 0) + c->memo[k + 1][l] ;
            }*/
            if (! isBase(Xk))  /* skip ccharacter in Xi that is not a base */
            {  ManageBaseError( Xk ) ;
            res = c->memo[l] ;
            continue;
            }
            else if (! isBase(Yl))  /* skip ccharacter in Yj that is not a base */
            {  ManageBaseError( Yl ) ;
            res = c->memo[l] ;
            c->memo[l] = c->memo[l + 1];
            }
            else  
            {  /* Note that stopping conditions (i==M) and (j==N) are already stored in c->memo (cf EditDistance_NW_Rec) */ 
            long min = /* initialization  with cas 1*/
                        ( isUnknownBase(Xk) ?  SUBSTITUTION_UNKNOWN_COST 
                            : ( isSameBase(Xk, Yl) ? 0 : SUBSTITUTION_COST ) 
                        )
                        + res ; 
            { long cas2 = INSERTION_COST + c->memo[l] ;      
            if (cas2 < min) min = cas2 ;
            }
            { long cas3 = INSERTION_COST + c->memo[l + 1] ;      
            if (cas3 < min) min = cas3 ; 
            }
            res = c->memo[l];
            c->memo[l] = min ;
            }
        //c->memo[i][j] = res ;
        }
    }return c->memo[j] ;
    //return res;
}
/***************************CACUL_BLOC*********************************/
static void EditDistance_NW_CaculBloc(struct NW_MemoContext *c, size_t I, size_t J, size_t K1, size_t K2){
    for (size_t k = J - 1; (int64_t) k >= (int64_t) (J - K2); k--){
        if (k + 1 == c->M)
        {
            c->strip[k + 1] = c->memo[I - K1];
        }
        
        char Xk = c->X[k];
        long res = c->memo[I];
        c->memo[I] = c->strip[k];
        for (size_t l = I - 1; (int64_t) l >= (int64_t) (I - K1); l--)
        {
            char Yl = c->Y[l];
            //if (k == c->M) c->memo[l] = (isBase(Yl) ? INSERTION_COST : 0) + c->memo[l + 1];
            if (! isBase(Xk))  /* skip ccharacter in Xi that is not a base */
            {  ManageBaseError( Xk ) ;
            res = c->memo[l] ;
            continue;
            }
            else if (! isBase(Yl))  /* skip ccharacter in Yj that is not a base */
            {  ManageBaseError( Yl ) ;
            res = c->memo[l] ;
            c->memo[l] = c->memo[l + 1];
            }
            else  
            {  /* Note that stopping conditions (i==M) and (j==N) are already stored in c->memo (cf EditDistance_NW_Rec) */ 
            long min = /* initialization  with cas 1*/
                        ( isUnknownBase(Xk) ?  SUBSTITUTION_UNKNOWN_COST 
                            : ( isSameBase(Xk, Yl) ? 0 : SUBSTITUTION_COST ) 
                        )
                        + res ; 
            { long cas2 = INSERTION_COST + c->memo[l] ;      
            if (cas2 < min) min = cas2 ;
            }
            { long cas3 = INSERTION_COST + c->memo[l + 1] ;      
            if (cas3 < min) min = cas3 ; 
            }
            res = c->memo[l];
            c->memo[l] = min ;
            }
        }c->strip[k] = c->memo[I - K1];
    }
}    

/*****************************CACHE AWARE*************************/
static long EditDistance_NW_CacheAw(struct NW_MemoContext *c, size_t i, size_t j, size_t K){
    c->strip[c->M] = 0;
    c->memo[c->N] = 0;
    for (size_t k = c->M - 1; (int64_t) k >= (int64_t) i ; k--)
    {
        char Xk = c->X[k];
        c->strip[k] = (isBase(Xk) ? INSERTION_COST : 0) + c->strip[k + 1] ;
    }
    for (size_t l = c->N - 1; (int64_t) l >= (int64_t) j ; l--)
    {
        char Yl = c->Y[l];
        c->memo[l] = (isBase(Yl) ? INSERTION_COST : 0) + c->memo[l + 1] ;
    }

    for (size_t I = c->N; (int64_t) I >= (int64_t) j; I -= K)
    {
        //printf("FFFIIINNN%ld\n", t);
        size_t K1 = (((int64_t) (I - K) >= (int64_t) j) ? K: I - j);
        for (size_t J = c->M; (int64_t) J >= (int64_t) i; J -= K)
        {
            size_t K2 = (((int64_t) (J - K) >= (int64_t) i) ? K: J - i);
            EditDistance_NW_CaculBloc(c, I, J, K1, K2);
            
        }
        
    }return c->memo[j];
}
/**************************CACHE_OBLIVIOUS*********************************/
static void CalculBlocRec(struct NW_MemoContext* c, size_t I, size_t J, size_t K1, size_t K2){
    if ((K1 <= S) && (K2 <= S)) EditDistance_NW_CaculBloc(c, I, J, K1, K2);
    else{
        if (K1 > S){
            CalculBlocRec(c, I, J, K1/2, K2);
            CalculBlocRec(c, I - K1/2, J, K1 - K1/2, K2);
        }else if (K2 > S){
            CalculBlocRec(c, I, J, K1, K2/2);
            CalculBlocRec(c, I, J - K2/2, K1, K2 - K2/2);
        }
    }
}

static long EditDistance_NW_CO(struct NW_MemoContext *c, size_t i, size_t j, size_t Seuil)
{
    S = Seuil;
    c->strip[c->M] = 0;
    c->memo[c->N] = 0;
    for (size_t k = c->M - 1; (int64_t) k >= (int64_t) i ; k--)
    {
        char Xk = c->X[k];
        c->strip[k] = (isBase(Xk) ? INSERTION_COST : 0) + c->strip[k + 1] ;
    }
    for (size_t l = c->N - 1; (int64_t) l >= (int64_t) j ; l--)
    {
        char Yl = c->Y[l];
        c->memo[l] = (isBase(Yl) ? INSERTION_COST : 0) + c->memo[l + 1] ;
    }
    CalculBlocRec(c, c->N, c->M, c->N, c->M);
    return c->memo[j];
}

/* EditDistance_NW_Rec :  is the main function to call, cf .h for specification 
 * It allocates and initailizes data (NW_MemoContext) for memoization and call the 
 * recursivefunction EditDistance_NW_RecMemo 
 * See .h file for documentation
 */
long EditDistance_NW_Rec2(char* A, size_t lengthA, char* B, size_t lengthB)
{
    //printf("memory allocated\n");
   _init_base_match() ;
   struct NW_MemoContext ctx;
   if (lengthA >= lengthB) /* X is the longest sequence, Y the shortest */
   {  ctx.X = A ;
      ctx.M = lengthA ;
      ctx.Y = B ;
      ctx.N = lengthB ;
   }
   else
   {  ctx.X = B ;
      ctx.M = lengthB ;
      ctx.Y = A ;
      ctx.N = lengthA ;
   }
   size_t M = ctx.M ;
   size_t N = ctx.N ;
   {  /* Allocation and initialization of ctx.memo to NOT_YET_COMPUTED*/
      /* Note: memo is of size (N+1)*(M+1) but is stored as (M+1) distinct arrays each with (N+1) continuous elements 
       * It would have been possible to allocate only one big array memezone of (M+1)*(N+1) elements 
       * and then memo as an array of (M+1) pointers, the memo[i] being the address of memzone[i*(N+1)].
       */ 
    ctx.memo = (long *) malloc ( (N+1) * sizeof(long)) ;
    ctx.strip = (long *) malloc ( (M+1) * sizeof(long)) ;
    //printf("memory allocated\n");

   }                                                                                                                                                    
   
   /* Compute phi(0,0) = ctx.memo[0][0] by calling the recursive function EditDistance_NW_RecMemo */
   // long res = EditDistance_NW_CO( &ctx, 0, 0, 20);
   long res = EditDistance_NW_CacheAw( &ctx, 0, 0, 20);

   free(ctx.memo);
   free(ctx.strip);
   return res ;
}

