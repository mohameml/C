#include <stdio.h>
#include <unistd.h>


int main(void)
{
    int id = fork();
    printf("the id is %d \n", id );

    sleep(3);

    if(id==-1)
    {
        perror("il y'a un errure \n");
    }

    if(id==0)
    {
        printf("Hello from th processus child \n");
        printf("My pid is : %d  \n", getpid());
    }
    else
    {
        printf("the pid of my child is : %d \n" , id);

        printf("Hello from the processus main \n");
    }

    return 0 ;
}