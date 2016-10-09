#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include "list.h"

double fract(double v) {
    int32_t i = (int32_t)v;
    return v-((double)i);
}

int main() {
    printf("List debug thingy!\n");
    List* l = newList(sizeof(double));
    int i = 0;

    for (i = 0; i < 100; i++) {
        double val = rand()%100 + fract(.0001 * rand());
        ListAdd(l, &val);
    }
    for (i = 0; i < l->count; i++) {
        double val = *(double*)ListGet(l, i);
        printf("%f\n",val);
    }

    return 0;
}
