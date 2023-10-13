#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>



int main(void)
{
    int arrya[5];

    int fd = open("sum", O_RDONLY);

    if(fd==-1)
    {
        printf("Error");
        return 1 ;
    }


    for(int i=0 ; i<5 ; i++)
    {
        read(fd , &arrya[i], sizeof(int));

        printf("Recevied %d \n", arrya[i]);
    }

    int sum = 0 ;

    for(int i=0 ; i<5 ; i++)
    {
        sum+=arrya[i];
    }


    printf("Somme of the numbres received from process 1 is : %d \n", sum);


    close(fd);


    int fd2 = open("sum",O_WRONLY);

    if(fd2==-1)
    {
        printf("Error \n");

        return 1 ;
    }


    write(fd2,&sum,sizeof(sum));


    close(fd2);






    return 0 ;


}