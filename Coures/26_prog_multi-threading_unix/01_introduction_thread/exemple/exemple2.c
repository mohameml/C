#include <stdio.h>
#include <pthread.h>


struct data_th
{
    const int n ;
    int tab[5];
    int res ;
    
};



void *routine_th(void * arg)
{
    struct data_th*  d1 = (struct data_th*)arg ;

    for(int i =0 ; i <d1->n ; i++)
    {
        d1->res+= d1->tab[i];
    }

    return NULL;
} 

int main(void)
{
    pthread_t th1 , th2 ;
    struct data_th  data1 = {5 , {1,2,3,4,5} , 0 };
    struct data_th  data2 = {5 , {6,7,8,9,10} , 0 };
    
    pthread_create(&th1,NULL , &routine_th , &data1);
    pthread_create(&th2 , NULL , &routine_th ,&data2);


    pthread_join(th1 ,NULL);
    pthread_join(th2 ,NULL);


    printf("le resulat fianl est : %d \n" , data1.res + data2.res);

    return 0 ;



}