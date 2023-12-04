#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>



/*----- déclaration du semaphore ------*/
sem_t sem ;

void* routine(void* arg)
{
    sem_wait(&sem); /* la fonction P du sémaphore  : s.C0-- */
    sleep(1);
    printf("Hello from routine \n");
    sem_post(&sem); /* la fonction V du sémaphore  : s.C0++ */

    return NULL ;
}


int main(void)
{

    /*------ initialisation du sémaphore: -------*/
    sem_init(&sem , 0 , 1); /*0 : si on  seulle processus , 1 : valeur initiale du processus*/

    pthread_t th[2];

    for(int i=0 ; i< 2 ;i++)
    {
        if(pthread_create(&th[i] , NULL , &routine , NULL)!=0)
        {
            printf("Faild to create Thread %d \n", i);
        }
    }



    for(int i = 0  ; i < 2 ; i++)
    {
        if(pthread_join(th[i] , NULL)!=0)
        {
            printf("Faild to join Thread %d \n" , i);
        }
    }



    /*---- libération de sémaphores -----*/
    sem_destroy(&sem);


    return 0 ;
}


