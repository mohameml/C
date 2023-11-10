#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void* routine()
{
    printf("Test from thraeds \n");

    // pour montrer la parallélisme 
    sleep(3);


    printf("Ending thraed \n");

    pthread_exit(NULL);
}


int main(void)
{
    pthread_t t1 , t2 ;
    
    
    if (pthread_create(&t1,NULL,&routine,NULL)!=0)
    {
        return EXIT_FAILURE;
    }

    if(pthread_create(&t2,NULL,&routine,NULL)!=0)
    {
        return EXIT_FAILURE;
    }

    pthread_exit(0);
    if(pthread_join(t1,NULL)!=0)
    {
        return EXIT_FAILURE;
    }
    
    if(pthread_join(t2,NULL)!=0)
    {
        return EXIT_FAILURE;
    }


    // return 0 ;

}