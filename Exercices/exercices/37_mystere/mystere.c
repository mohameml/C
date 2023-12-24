#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
int64_t f(int64_t n){int64_t x,y;if(n < 2){return n;}x=f(n-1);y=f(n-2);return x+y;}int main(void){int64_t z=42+1;printf("%ld\n",f(z));return 0;}

