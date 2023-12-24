#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
/*

l'objcetif de ce exercie et de programmer avec le moniteur une solution sur le pb du producteur et conssomatteur 


*/

#define N 10 
#define NBThreads 2

int tampon[N] ;

int count = 0 ;


pthread_mutex_t mutex ;

/*----------- moniteur qui controle le nombre des palces disponibles dans le tampon : ----------- */

pthread_cond_t condFull ;



/*----------- moniteur qui controle le nombre des palces pleines : ----------- */

pthread_cond_t condEmpty ;


/*------------ */


void* production()
{

    /*
        la phase de production on génere un nombre aléatoire :
    */


   while(1)
   {

    pthread_mutex_lock(&mutex);
    

    int x = rand() % 10;
    sleep(1); 

    // on va consulter est ce que il y'a uhne place disponible dans le tampon :

        while(count == N)
        {
                pthread_cond_wait(&condEmpty , &mutex);
        }


        tampon[count] = x ;
        count++;
        printf("Production of %d \n" , x);

        pthread_cond_signal(&condFull);
        pthread_mutex_unlock(&mutex);


   }



}

void* consommation()
{
    /*
        la pahse de consommation :
    */



   while(1)
   {


        pthread_mutex_lock(&mutex);

        while(count == 0)
        {
            // la tampon est vide :
            pthread_cond_wait(&condFull , &mutex);
        }

        int y = tampon[count - 1];
        count--;

        printf("Consommation de %d \n", y);

        pthread_cond_signal(&condEmpty);

        pthread_mutex_unlock(&mutex);
   }


}


int main(void)
{
    srand(time(NULL));

    pthread_mutex_init(&mutex , NULL);
    pthread_cond_init(&condFull , NULL);

    pthread_cond_init(&condEmpty , NULL);


    /*----------- des threads pour simuler ole pb : -----------*/

    pthread_t th[NBThreads];


    for(int i =0 ; i<NBThreads ; i++)
    {
        if(i%2==0)
        {
            if(pthread_create(&th[i] , NULL , &production , NULL)!=0)
            {
                perror("Errure lors de la creation de Thread :!!!");
            }
        }
        else
        {
            if(pthread_create(&th[i] , NULL , &consommation , NULL)!=0)
            {
                perror("Errure lors de la creation de Thread :!!!");
            }            
        }
    }


    for(int i =0 ; i< NBThreads ; i++)
    {
        if(pthread_join(th[i] , NULL)!=0)
        {
            perror("Erreur lors de la join d'un Thread ");
        }
    }



    /*--------- libération des ressources : ---------------*/
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condFull);
    pthread_cond_destroy(&condEmpty);

    return 0 ;
}