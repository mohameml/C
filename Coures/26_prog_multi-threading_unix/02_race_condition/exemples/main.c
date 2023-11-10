#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


int sum = 0 ;

void* routine()
{   
    for(int i=0 ; i<1000000;i++)
    {
        
        sum++; 
        // 	movl sum(%rip), %eax
        // addl	$1, %eax
        // movl	%eax, sum(%rip)

    }


    return NULL ;
}



int main(void)
{
    pthread_t t1 , t2 ;

    pthread_create(&t1 , NULL , &routine , NULL);
    
    pthread_create(&t2 , NULL , &routine , NULL);

    pthread_join(t1,NULL);
    pthread_join(t2, NULL);

    printf("%d \n", sum);
    return 0 ;
}