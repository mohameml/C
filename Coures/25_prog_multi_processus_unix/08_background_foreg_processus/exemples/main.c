#include <stdio.h>
#include <signal.h>

void handel_signal(int signal_){

	if(signal_==SIGTSTP){
		printf("\nthis is ignore!\n");
	}
}


int main(void)
{

    int x ;
    printf("Write here you number please : ... ");
    scanf("%d",&x);

    printf("the Result of %d * 2 = %d \n ", x , x*2);


    // now we will change the defautl action with CTRL+Z :

    // Méthode 1 : signal 
    signal(SIGTSTP,handel_signal);
    
    
    // Méthode 2 :sigcation 
    
    
    return 0 ;
}
