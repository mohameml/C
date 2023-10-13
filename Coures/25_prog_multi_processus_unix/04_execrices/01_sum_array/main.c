#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(void)
{
    int array[] = {1,3,4,5,6,0,1};
    int length = sizeof(array)/sizeof(int);

    int start , end ;

    int fd[2];

    if(pipe(fd)==-1)
    {
        perror("Got Error when the opening the pipe \n");

        return 1 ;
    }

    int id = fork();

    if(id==-1)
    {
        return 1 ; // en cas d'errure 
    }

    if(id==0)
    {

        start = 0 ;
        end = length/2 ;
    }
    else 
    {
        // processus father 
        start = length/2 ;
        end = length ;
    }


    // calucl the half-some 

    int i ;

    int sum = 0 ;

    for(i=start;i<end ; i++)
    {
        sum+=array[i];
    }


    printf("the somme of the half-array is : %d \n", sum);

    // now the communication of the two processus 

    if(id==0)
    {
        // the processus child 
        close(fd[0]);
        write(fd[1],&sum,sizeof(sum));
        close(fd[1]);
    }
    else 
    {
        int sumfromchild;
        close(fd[1]);
        read(fd[0],&sumfromchild,sizeof(sumfromchild));
        close(fd[0]);
    
        printf("the sum totla of the numbers in the arrya is : %d \n", sum+sumfromchild);
    
    
    }











    return 0 ;

    
    
}