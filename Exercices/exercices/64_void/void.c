#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static void print_byte(uint8_t byte)
{
}

static void print_memory(void *base, size_t size)
{
}


int main(void)
{
    uint8_t un = 1;
    print_memory(&un, sizeof(uint8_t));

    uint8_t tab[4] = { 255, 0, 255, 0 };
    print_memory(tab, 4 * sizeof(uint8_t));

    uint32_t foo = 123456;
    printf("%u = ", foo);
    print_memory(&foo, sizeof(uint32_t));
    printf("\n");

    return EXIT_SUCCESS;
}
