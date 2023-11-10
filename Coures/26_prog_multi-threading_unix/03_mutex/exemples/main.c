#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


int sum = 0 ;

pthread_mutex_t mutex ;

void* routine()
{   
    pthread_mutex_lock(&mutex);  
    for(int i=0 ; i<1000000;i++)
    {
        
        sum++; 
        // 	movl sum(%rip), %eax
        // addl	$1, %eax
        // movl	%eax, sum(%rip)

    }
    
    pthread_mutex_unlock(&mutex);


    return NULL ;
}



int main(void)
{
    pthread_t t1 , t2 ;
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&t1 , NULL , &routine , NULL);
    
    pthread_create(&t2 , NULL , &routine , NULL);

    pthread_join(t1,NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    printf("%d \n", sum);
    return 0 ;
}