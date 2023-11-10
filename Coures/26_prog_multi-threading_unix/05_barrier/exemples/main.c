#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>



pthread_barrier_t barrier ;


void* routine()
{
    sleep(1);
    printf("waitting in the barrier \n");

    pthread_barrier_wait(&barrier);
    sleep(1);
    printf("we are passed the barrier \n");

    return NULL;
}


int main(void)
{

    pthread_t th[10];


    pthread_barrier_init(&barrier,NULL ,10);


    for(int i=0 ; i<10 ; i++)
    {
        if(pthread_create(&th[i],NULL,&routine , NULL)!=0)
        {
            perror("Faild to create  thread \n");
        }
    }


    for(int i =0 ; i < 10 ; i++)
    {
        if(pthread_join(th[i],NULL)!=0)
        {
            perror("faild to join  thread \n");
        }
    }


    pthread_barrier_destroy(&barrier);


    return 0 ;
}






