#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define n 10 

int arr[10] = {1,2,3,4,5,6,7,8,9,10};


void* routine(void* arg)
{
    // sleep(1);
    int index = *((int*)arg);

    printf("%d \n", arr[index]);
    free(arg);
}

int main(void)
{
    pthread_t th[10] ;



    for(int i=0 ; i<10 ; i++)
    {
        int* arg = malloc(sizeof(int));
        *arg = i ;
        if(pthread_create(&th[i],NULL, &routine,arg)!=0)
        {
            printf("erreur lors de la création d'un Thread \n");
        }

    }


    for(int i=0 ; i<10 ; i++)
    {
        if(pthread_join(th[i],NULL)!=0)
        {
            printf("erreur in join thread  \n");
        }
    }




    return 0 ;


}