#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int fuel =0 ;

pthread_mutex_t mutex ;
pthread_cond_t condFuel ;


void* fuel_filling()
{

    for(int i =0 ; i<5 ; i++)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        fuel+=15;
        printf("Filled  fuel ... %d \n", fuel);

        pthread_cond_signal(&condFuel);
        pthread_mutex_unlock(&mutex);

    }

}

void* car()
{
    pthread_mutex_lock(&mutex);

    while(fuel < 40)
    {
        printf("No fuel ... just waiting .....%d \n", fuel);

        pthread_cond_wait(&condFuel,&mutex);
        

    }
    fuel-=40;
    printf("got the  fuel. Now left : %d \n", fuel);
    pthread_mutex_unlock(&mutex);

}


int main(void)
{
    pthread_t th[2];
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&condFuel,NULL);

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
    pthread_cond_destroy(&condFuel);
    return 0 ;
}