#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

# define N 4 

sem_t sem ;
pthread_mutex_t mutex ;


int somme = 0 ;

void* routine1()
{
    while(1)
    {
        // pthread_mutex_lock(&mutex);
        sem_wait(&sem);
        somme++ ;
        printf("la valeur actuelle de somme = %d \n" , somme);
        // sem_post(&sem);
        // pthread_mutex_unlock(&mutex);
    }

    


}



void* routine2()
{
    while(1)
    {
        // pthread_mutex_unlock(&mutex);
        sem_post(&sem);
        usleep(50000);
    }

}


int main(void)
{
    /*----- init ------*/
    sem_init(&sem , 0 ,1);
    pthread_mutex_init(&mutex , NULL);


    pthread_t th[N];

    for(int i =0 ; i< N ; i++)
    {
        if(i%2==0)
        {
            if(pthread_create(&th[i], NULL , &routine1 , NULL)!=0)
            {
                printf("Faild to create Thread %d \n", i);
            }
        }
        else 
        {
            if(pthread_create(&th[i], NULL , &routine2 , NULL)!=0)
            {
                printf("Faild to create Thread %d \n", i);
            }           
        }
    }



    for(int i = 0 ; i < N ; i++)
    {
        if(pthread_join(th[i] ,NULL)!=0)
        {
            printf("Faild to join %d \n" , i);
        }
    }



    return 0 ;
}