#include <stdlib.h>
#include "util.h"

void panic(char* message) {
    printf("\n\nPanic! Something happened that shouldnt have!\nDetails:\n");
    printf(message);
    printf("\n\nProgram Terminated.\n\n");
    exit(-1);
}
