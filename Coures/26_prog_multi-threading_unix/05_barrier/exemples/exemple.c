#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*----- déclaration de la barrier b : --------*/
pthread_barrier_t b ;


/*--------- la fonction routine de thread ---------------*/
void* routine()
{
    sleep(1);
    printf("waitting in the barrier \n");

    pthread_barrier_wait(&b);
    sleep(1);
    printf("we are passed the barrier \n");

    return NULL;


    
}






int main(void)
{
    /*---------- déclaration de 10 Threads :---------------*/
    pthread_t th[10];

    /*----------- initialisation de la  barrier : barrier de 10 Threads ------------*/
    pthread_barrier_init(&b , NULL , 10);


    /*-------------- initialistion de 10 threads ---------------------*/
    for(int i =0 ; i < 10 ; i++)
    {
        if(pthread_create(&th[i], NULL , &routine , NULL)!=0)
        {
            printf("Faild to create thread %d \n" , i);
        }
    }


    /*---------------- Attente du 10 Threads --------------------*/
    for(int j =0 ; j <10 ; j++)
    {
        if(pthread_join(th[j] , NULL)!=0)
        {
            printf("Faild to join thread %d \n" , j);
        }
    }



    /*------------ libération des ressources de la  barriere -------------*/
    pthread_barrier_destroy(&b);


    return 0 ;

}