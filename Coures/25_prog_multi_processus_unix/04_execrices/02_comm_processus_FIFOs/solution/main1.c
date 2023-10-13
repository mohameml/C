#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
    srand(time(NULL));

    int array[5];

    for(int i = 0 ; i<5 ;i++)
    {
        array[i]=rand() % 100 ;
    }

    int fd = open("sum",O_WRONLY);

    if(fd==-1)
    {
        printf("error ");
        return 1 ;
    }


    for(int i=0 ; i<5 ; i++)
    {
        write(fd ,&array[i],sizeof(int));

        printf("Wrote %d\n", array[i]);
    }

    close(fd);

    int fd2 = open("sum",O_RDONLY);
    if(fd2==-1)
    {
        printf("Error \n");
        return 1 ;
    }

    int sum_from_main2;

    read(fd2 , &sum_from_main2, sizeof(sum_from_main2));

    printf("the somme recevied from the main2 is : %d \n", sum_from_main2);
    close(fd2);

    return 0 ;

}