#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N 8

sem_t semFull ;
sem_t semEmpty ;

pthread_mutex_t m ;

/*------- tampon :------*/
int tampon[10];
int count = 0 ;

void* productuer(void* args)
{
    while(1)
    {
        // production :
        int x = rand() % 100 ; /*------ génere un nombre aléatoie entre 0 , 100 -------*/
        sleep(1);
        // 
        sem_wait(&semEmpty);
        pthread_mutex_lock(&m);
        
        tampon[count] = x ;
        count++;
        printf("Production du %d \n" , x);


        pthread_mutex_unlock(&m);
        sem_post(&semFull);
    }


}



void* consommateur(void* args)
{
    while(1)
    {
        int y ;

        // consommation :
        sem_wait(&semFull);
        pthread_mutex_lock(&m);
        y = tampon[count -1];
        count--;    

        pthread_mutex_unlock(&m);
        
        sem_post(&semEmpty);

        printf("Consomation du : %d \n", y);
        // sleep(1);
    }


}

int main(void)
{

    /*
    SemFull : controle le nombre cases déja utilisés par le productuer 
    SemFull : bloque le consommateur si le valeur égale à 0 
    semFull : la valeur initiale égale à 0 .    
    */
    sem_init(&semFull , 0 , 0); 
    
    /*
    semEmpty : controle le nombre des ressources disponibles (ie les cases Empty )
    semEmpty : bloque le productuer si le nombre des ressources Empty éfale à 0 
    semEmpty :  la valeur initiale est égale à la valeur initiale des ressources (ici 10);
    */
    sem_init(&semEmpty , 0 ,  10); 

    pthread_mutex_init(&m , NULL);

    /*-------- pour génerer des nombres aléatoires :------------*/
    srand(time(NULL));

    pthread_t th[N];


    for(int i =0 ; i< N ; i++)
    {
        if(i > 0)
        {
            if(pthread_create(&th[i] , NULL ,&productuer, NULL )!=0)
            {
                printf("Faild to create Thread %d " , i);
                return 1 ;
            }
        }
        else
        {
            if(pthread_create(&th[i] , NULL ,&consommateur, NULL )!=0)
            {
                printf("Faild to create Thread %d " , i);
                return 1 ;
            }         
        }
    }


    for(int i =0 ; i<N ; i++)
    {
        if(pthread_join(th[i] , NULL)!=0)
        {
            printf("Faild to join Thread %d \n", i);
        }
    }


    pthread_mutex_destroy(&m);

    return 0 ;

}