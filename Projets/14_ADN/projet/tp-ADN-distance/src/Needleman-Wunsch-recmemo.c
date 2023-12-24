
#include "Needleman-Wunsch-recmemo.h"
#include <stdio.h>  
#include <stdlib.h> 
#include <stdint.h>
#include <string.h> /* for strchr */
#include "characters_to_base.h" /* mapping from char to base */



/*****************************************************************************/
   
/* Context of the memoization : passed to all recursive calls */
/** \def NOT_YET_COMPUTED
 * \brief default value for memoization of minimal distance (defined as an impossible value for a distance, -1).
 */
#define NOT_YET_COMPUTED -1L 




// -------------------------------------------------------------- version récursif avec memoisation  -------------------------------------------
// -------------------------------------------------------------- version récursif avec  memoisation -------------------------------------------
// -------------------------------------------------------------- version récursif avec memoisation  -------------------------------------------


/** \struct NW_MemoContext
 * \brief data for memoization of recursive Needleman-Wunsch algorithm 
*/

struct NW_MemoContext 
{
    char *X ; /*!< the longest genetic sequences */
    char *Y ; /*!< the shortest genetic sequences */
    size_t M; /*!< length of X */
    size_t N; /*!< length of Y,  N <= M */
    long **memo; /*!< memoization table to store memo[0..M][0..N] (including stopping conditions phi(M,j) and phi(i,N) */
} ;

/*
 *  static long EditDistance_NW_RecMemo(struct NW_MemoContext *c, size_t i, size_t j) 
 * \brief  EditDistance_NW_RecMemo :  Private (static)  recursive function with memoization \
 * direct implementation of Needleman-Wursch extended to manage FASTA sequences (cf TP description)
 * \param c : data passed for recursive calls that includes the memoization array 
 * \param i : starting position of the left sequence :  c->X[ i .. c->M ] 
 * \param j : starting position of the right sequence :  c->Y[ j .. c->N ] 
 */ 




/* compute and returns phi(i,j) using data in c -allocated and initialized by EditDistance_NW_Rec */

static long EditDistance_NW_RecMemo(struct NW_MemoContext *c, size_t i, size_t j) 
{
   if (c->memo[i][j] == NOT_YET_COMPUTED)
   {  
      long res ;
      char Xi = c->X[i] ;
      char Yj = c->Y[j] ;

      if (i == c->M) /* Reach end of X */
      {  
         if (j == c->N) res = 0;  /* Reach end of Y too */
         
         else res = (isBase(Yj) ? INSERTION_COST : 0) + EditDistance_NW_RecMemo(c, i, j+1) ;
      }
      else if (j == c->N) /* Reach end of Y but not end of X */
      {  res = (isBase(Xi) ? INSERTION_COST : 0) + EditDistance_NW_RecMemo(c, i+1, j) ;
      }
      else if (! isBase(Xi))  /* skip ccharacter in Xi that is not a base */
      {  ManageBaseError( Xi ) ;
         res = EditDistance_NW_RecMemo(c, i+1, j) ;
      }
      else if (! isBase(Yj))  /* skip ccharacter in Yj that is not a base */
      {  ManageBaseError( Yj ) ;
         res = EditDistance_NW_RecMemo(c, i, j+1) ;
      }
      else  
      {  /* Note that stopping conditions (i==M) and (j==N) are already stored in c->memo (cf EditDistance_NW_Rec) */ 
         long min = /* initialization  with cas 1*/
                   ( isUnknownBase(Xi) ?  SUBSTITUTION_UNKNOWN_COST 
                          : ( isSameBase(Xi, Yj) ? 0 : SUBSTITUTION_COST ) 
                   )
                   + EditDistance_NW_RecMemo(c, i+1, j+1) ; 
         { long cas2 = INSERTION_COST + EditDistance_NW_RecMemo(c, i+1, j) ;      
           if (cas2 < min) min = cas2 ;
         }
         { long cas3 = INSERTION_COST + EditDistance_NW_RecMemo(c, i, j+1) ;      
           if (cas3 < min) min = cas3 ; 
         }
         res = min ;
      }
       c->memo[i][j] = res ;
   }
   return c->memo[i][j] ;
}

/* EditDistance_NW_Rec :  is the main function to call, cf .h for specification 
 * It allocates and initailizes data (NW_MemoContext) for memoization and call the 
 * recursivefunction EditDistance_NW_RecMemo 
 * See .h file for documentation
 */
long EditDistance_NW_Rec(char* A, size_t lengthA, char* B, size_t lengthB)
{
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
      ctx.memo = (long **) malloc ( (M+1) * sizeof(long *)) ;
      if (ctx.memo == NULL) { perror("EditDistance_NW_Rec: malloc of ctx_memo" ); exit(EXIT_FAILURE); }
      for (int i=0; i <= M; ++i) 
      {  ctx.memo[i] = (long*) malloc( (N+1) * sizeof(long));
         if (ctx.memo[i] == NULL) { perror("EditDistance_NW_Rec: malloc of ctx_memo[i]" ); exit(EXIT_FAILURE); }
         for (int j=0; j<=N; ++j) ctx.memo[i][j] = NOT_YET_COMPUTED ;
      }
   }    
   
   /* Compute phi(0,0) = ctx.memo[0][0] by calling the recursive function EditDistance_NW_RecMemo */
   long res = EditDistance_NW_RecMemo( &ctx, 0, 0 ) ;
    
   { /* Deallocation of ctx.memo */
      for (int i=0; i <= M; ++i) free( ctx.memo[i] ) ;
      free( ctx.memo ) ;
   }
   return res ;
}




// -------------------------------------------------------------- version Iteratif -------------------------------------------
// -------------------------------------------------------------- version Iteratif -------------------------------------------
// -------------------------------------------------------------- version Iteratif -------------------------------------------


struct NW_MemoIter 
{
    char *X ; /*!< the longest genetic sequences */
    char *Y ; /*!< the shortest genetic sequences */
    size_t M; /*!< length of X */
    size_t N; /*!< length of Y,  N <= M */
    long *table; /* table de taille M+N  */
} ;




// la fonction correspond qui fait la coreespondance entre l'élemnt da la postion (i,j) dans  matrice et sa postion dans la table 

size_t correspond_ligne(size_t i , size_t j , size_t M)
{

   return j-i + M ;
}





static void EditDistance_NW_Iter_i_j(struct NW_MemoIter *c, size_t i, size_t j) 
/* compute and returns phi(i,j) using data in c -allocated and initialized by EditDistance_NW_Rec */
{ 
      long res ;
      char Xi = c->X[i] ;
      char Yj = c->Y[j] ;


      if (i == c->M) /* Reach end of X */
      {  
         if (j == c->N) res = 0;  /* Reach end of Y too */
         
         else res = (isBase(Yj) ? INSERTION_COST : 0) + c->table[correspond_ligne(i,j+1,c->M)] ;
      }

      else if (j == c->N) /* Reach end of Y but not end of X */
      {  
         res = (isBase(Xi) ? INSERTION_COST : 0) + c->table[correspond_ligne(i+1,j,c->M)] ;
      }

      else if (! isBase(Xi))  /* skip ccharacter in Xi that is not a base */
      { 
          ManageBaseError( Xi ) ;
         res =   c->table[correspond_ligne(i+1,j,c->M)] ;
      }
      else if (! isBase(Yj))  /* skip ccharacter in Yj that is not a base */
      { 
          ManageBaseError( Yj ) ;
         res = c->table[correspond_ligne(i,j+1,c->M)] ;
      }

      else  
      {  
         /* Note that stopping conditions (i==M) and (j==N) are already stored in c->memo (cf EditDistance_NW_Rec) */ 
         long min = /* initialization  with cas 1*/
                   ( isUnknownBase(Xi) ?  SUBSTITUTION_UNKNOWN_COST 
                          : ( isSameBase(Xi, Yj) ? 0 : SUBSTITUTION_COST ) 
                   )
                   + c->table[correspond_ligne(i+1,j+1,c->M)] ;

         { 
            long cas2 = INSERTION_COST + c->table[correspond_ligne(i+1,j,c->M)] ;  
           if (cas2 < min) min = cas2 ;

         }

         { 
            long cas3 = INSERTION_COST + c->table[correspond_ligne(i,j+1,c->M)] ;     
           if (cas3 < min) min = cas3 ; 
         }
         res = min ;
      }
       c->table[correspond_ligne(i,j,c->M)] = res ;
   
}


//  la fonction principale de la méthode iterative ---------------------- :


long EditDistance_NW_Iter(char* A, size_t lengthA, char* B, size_t lengthB)
{

   _init_base_match();
   struct NW_MemoIter ctx;

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

   ctx.table = (long *) malloc ( (M+N) * sizeof(long)) ;
   
   if (ctx.table == NULL)
   {
      perror("EditDistance_NW_Rec: malloc of ctx_memo" );
      exit(EXIT_FAILURE); 
   }


   // ---------------------------------

   
   // remplir ctx->tab :

   for( int i = M ; i >=0 ; i-- )
   {
      for( int j = N ; j >=0 ; j-- )
      {
         EditDistance_NW_Iter_i_j(&ctx, i , j);
      }
   }



   long res =  ctx.table[M];


    
   /* Deallocation of ctx.memo */
   free( ctx.table) ;
   

   return res ;




}



// ------------------------------------------ méthode cache aware ------------------------------------------------- 
// ------------------------------------------ méthode cache aware ------------------------------------------------- 
// ------------------------------------------ méthode cache aware ------------------------------------------------- 

struct NW_Memo
{
   char *X ; /*!< the longest genetic sequences */
   char *Y ; /*!< the shortest genetic sequences */
   size_t M; /*!< length of X */
   size_t N; /*!< length of Y,  N <= M */
   long *ligne; 
   long *colonne;
} ;


/***************************CACUL_BLOC*********************************/



static void EditDistance_NW_CaculBloc(struct NW_Memo *c, size_t I, size_t J, size_t K1, size_t K2)
{
   
   for (size_t k = J - 1; (int64_t) k >= (int64_t) (J - K2); k--)
   {

      char Xk = c->X[k];
      
      long res = c->ligne[I];
      
      c->ligne[I] = c->colonne[k];
      
      
      for (size_t l = I - 1; (int64_t) l >= (int64_t) (I - K1); l--)
      {
         char Yl = c->Y[l];
         
         //if (k == c->M) c->memo[l] = (isBase(Yl) ? INSERTION_COST : 0) + c->memo[l + 1];
            
         if (! isBase(Xk))  /* skip ccharacter in Xi that is not a base */
         {  
            ManageBaseError( Xk ) ;
            res = c->ligne[l] ;
            continue;
         }
         else if (! isBase(Yl))  /* skip ccharacter in Yj that is not a base */
         {  
            ManageBaseError( Yl ) ;
            res = c->ligne[l] ;
            c->ligne[l] = c->ligne[l + 1];
         }
         else  
         {  
            /* Note that stopping conditions (i==M) and (j==N) are already stored in c->memo (cf EditDistance_NW_Rec) */ 
            long min =
                  ( isUnknownBase(Xk) ?  SUBSTITUTION_UNKNOWN_COST 
                        : ( isSameBase(Xk, Yl) ? 0 : SUBSTITUTION_COST ) 
                  )
                  + res ; 
            
            
            long cas2 = INSERTION_COST + c->ligne[l] ;      
            if (cas2 < min) min = cas2 ;
            

             
            long cas3 = INSERTION_COST + c->ligne[l + 1] ;      
            if (cas3 < min) min = cas3 ; 
            

            res = c->ligne[l];
            c->ligne[l] = min ;
         }
      }
        
      c->colonne[k] = c->ligne[I - K1];
   }
}   


static long EditDistance_NW_CacheAw_i_j(struct NW_Memo *c, size_t K)
{
   c->colonne[c->M] = 0;
   c->ligne[c->N] = 0;


   size_t i = 0  ;
   size_t j =0 ;
   
   for (size_t k = c->M - 1; (int64_t) k >= (int64_t) i ; k--)
   {
      char Xk = c->X[k];
      c->colonne[k] = (isBase(Xk) ? INSERTION_COST : 0) + c->colonne[k + 1] ;
   }
    
   for (size_t l = c->N - 1; (int64_t) l >= (int64_t) j ; l--)
   {
      char Yl = c->Y[l];
      c->ligne[l] = (isBase(Yl) ? INSERTION_COST : 0) + c->ligne[l + 1] ;
   }


   for (size_t I = c->N; (int64_t) I >= (int64_t) j; I -= K)
   {
      size_t K1 = (((int64_t) (I - K) >= (int64_t) j) ? K: I - j);
        
      for (size_t J = c->M; (int64_t) J >= (int64_t) i; J -= K)
      {
         size_t K2 = (((int64_t) (J - K) >= (int64_t) i) ? K: J - i);
         EditDistance_NW_CaculBloc(c, I, J, K1, K2);
            
      }
        
   }
    
   return c->ligne[j];
   // return c->table[M]
}




// la fonction principale pour la méthode cache aware :

long EditDistance_NW_Aware(char* A, size_t lengthA, char* B, size_t lengthB)
{

   _init_base_match() ;
   struct NW_Memo ctx;
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

    ctx.ligne = (long *) malloc ( (N+1) * sizeof(long)) ;
    ctx.colonne = (long *) malloc ( (M+1) * sizeof(long)) ;                                                                                                                                                 
   
   long res = EditDistance_NW_CacheAw_i_j( &ctx, 20);

   // libération de la mémoire :

   free(ctx.ligne);
   free(ctx.colonne);
   return res ;


}




// ---------------------------------------------- cache oblivois ---------------------------------------
// ---------------------------------------------- cache oblivois ---------------------------------------
// ---------------------------------------------- cache oblivois ---------------------------------------




static size_t S; // pour le seuille 


 


static void CalculBlocRec(struct NW_Memo* c, size_t I, size_t J, size_t K1, size_t K2){
   
   
   if ((K1 <= S) && (K2 <= S)) 
   {
      EditDistance_NW_CaculBloc(c, I, J, K1, K2);
    
   } 
   else
   {
      if (K1 > S)
      {
         CalculBlocRec(c, I, J, K1/2, K2);
         CalculBlocRec(c, I - K1/2, J, K1 - K1/2, K2);
      }
      else if (K2 > S)
      {
         CalculBlocRec(c, I, J, K1, K2/2);
         CalculBlocRec(c, I, J - K2/2, K1, K2 - K2/2);
      }
    
   }
}


static long EditDistance_NW_CO(struct NW_Memo *c, size_t i, size_t j, size_t Seuil)
{
   S = Seuil;
   c->colonne[c->M] = 0;
   c->ligne[c->N] = 0;

   // --- init 
   for (size_t k = c->M - 1; (int64_t) k >= (int64_t) i ; k--)
   {
      char Xk = c->X[k];
      c->colonne[k] = (isBase(Xk) ? INSERTION_COST : 0) + c->colonne[k + 1] ;
   }

   // --- init :

   for (size_t l = c->N - 1; (int64_t) l >= (int64_t) j ; l--)
   {
      char Yl = c->Y[l];
      c->ligne[l] = (isBase(Yl) ? INSERTION_COST : 0) + c->ligne[l + 1] ;
   }


   CalculBlocRec(c, c->N, c->M, c->N, c->M);

   return c->ligne[j];
}


long EditDistance_NW_cache_Oblivous(char* A, size_t lengthA, char* B, size_t lengthB)
{

   _init_base_match() ;
   struct NW_Memo ctx;
   if (lengthA >= lengthB) 
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

   ctx.ligne = (long *) malloc ( (N+1) * sizeof(long)) ;
   ctx.colonne = (long *) malloc ( (M+1) * sizeof(long)) ;
                                                                                                                                                      
   
   long res = EditDistance_NW_CO( &ctx, 0, 0, 20);
   free(ctx.ligne);
   free(ctx.colonne);
   return res ;
}

