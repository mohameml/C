#include <stdio.h>
#include <pthread.h>


int x =0 ;

void* routine(void* arg)
{
    for(int i =0 ; i<1000000 ; i++)
    {
        x++;
    }

    return NULL; 
}

int main(void)
{
    pthread_t th[4];

    for(int i =0 ; i<4 ; i++)
    {
        pthread_create(&th[i], NULL , &routine , NULL);

        printf("thread %d has created \n", i);

        pthread_join(th[i], NULL);

        printf("Thread %d has finished execution \n", i);
    }



    printf("The result %d \n",x);

    return 0 ;

}