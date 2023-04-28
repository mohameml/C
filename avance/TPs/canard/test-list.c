#include <stdlib.h> // atof
#include <stdio.h>  // printf
#include "list.h"

bool doubleLessThan(void *data1, void *data2)
{
    return *(double*)data1 < *(double*)data2;
}

// list tester
int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Syntax: %s <number list>\n", argv[0]);
        return -1;
    }

    struct list *l = list_create(sizeof(double));

    for (int i = 1; i < argc; i++) {
        double read = atof(argv[i]);
        list_push_back(l, &read);
    }

    printf("list parsed:\n");
    list_FOR_EACH(l, double*, d)
        printf("%f ",*d);
    printf("\n\n");

    list_merge_sort(l, doubleLessThan);

    printf("list sorted:\n");
    list_FOR_EACH(l, double*, d)
        printf("%f ",*d);
    printf("\n\n");

    return 0;
}
