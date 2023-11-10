#include <stdio.h>
#include <pthread.h>


int x =0 ;
pthread_mutex_t mutex ;


void* routine(void* arg)
{
    pthread_mutex_lock(&mutex);
    for(int i =0 ; i<1000000 ; i++)
    {
        x++;
    }

    pthread_mutex_unlock(&mutex);
    return NULL; 
}

int main(void)
{
    pthread_t th[4];
    pthread_mutex_init(&mutex , NULL);

    for(int i =0 ; i<4 ; i++)
    {
        pthread_create(&th[i], NULL , &routine , NULL);

        printf("thread %d has created \n", i);


    }

    for(int i=0 ; i<4 ; i++)
    {
        pthread_join(th[i], NULL);

        printf("Thread %d has finished execution \n", i);
    }



    printf("The result %d \n",x);

    pthread_mutex_destroy(&mutex);
    return 0 ;

}