#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


int main(void)
{
    uint32_t n = 500;

    for (uint32_t i = 0; i < n; i++) {
        fprintf(stdout, "ping %d ", i);
        fprintf(stderr, "pong %d\n", i);
    }

    return EXIT_SUCCESS;
}
