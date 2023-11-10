#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


void* roll_dice()
{
    int value = rand()%10 ;
    int* resultat = malloc(sizeof(int));
    *resultat = value;
    printf("The value of value is : %d \n",value);

    return (void * )resultat ;
}


int main(void)
{

    int* res ;

    srand(time(NULL));
    pthread_t t1 ;

    pthread_create(&t1 , NULL ,&roll_dice , NULL);

    pthread_join(t1,(void **)&res);




    printf("Thevalue of res is :%d \n", *res);

    free(res);
    return 0 ;
}