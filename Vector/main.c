#include <stdio.h>
#include <stdlib.h>
#include "vector3.h"

int main() {
    printf("Hello world!\n");
    printf("Poopy!\n");

    Vector3* blah = newVector3(3,2,4);
    printf("\n\nI has an vector!\n");


    float mag = length(blah);
    printf("its length is %f units\n", mag);

    Vector3* nrmd = normalized(blah);
    printf("i done normalized it to %f units\n", length(nrmd));

    if (length(nrmd)) {
        panic("Length of a normalized vector was one, and that's exactly what I expected.");
    }

    printf("\n\ndone");
    return 0;
}
