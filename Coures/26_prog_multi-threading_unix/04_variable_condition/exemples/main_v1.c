#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int fuel =0 ;

pthread_mutex_t mutex ;

void* fuel_filling()
{

    for(int i =0 ; i<5 ; i++)
    {
        pthread_mutex_lock(&mutex);
        fuel+=15;
        printf("Filled  fuel ... %d \n", fuel);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

}

void* car()
{
    pthread_mutex_lock(&mutex);
    fuel-=40;
    printf("got the  fuel. Now left : %d \n", fuel);
    pthread_mutex_unlock(&mutex);

}


int main(void)
{
    pthread_t th[2];
    pthread_mutex_init(&mutex,NULL);

    for(int i=0 ; i<2;i++)
    {
        if(i==0)
        {
            if(pthread_create(&th[i], NULL , &car, NULL))
            {
                printf("Erreur lors de lac création de Thread \n");
                return 1 ;
            }
        }
        else 
        {
            if(pthread_create(&th[i], NULL , &fuel_filling, NULL))
            {
                printf("Erreur lors de lac création de Thread \n");
                return 1 ;
            }           
        }
    }


    for(int i=0 ; i<2 ; i++)
    {
        if(pthread_join(th[i],NULL))
        {
            printf("Failed to join hte Threa \n");
        }
    }


    pthread_mutex_destroy(&mutex);
    return 0 ;
}