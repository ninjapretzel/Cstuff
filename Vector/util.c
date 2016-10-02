#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void panic(char* message) {
    printf("\n\nPanic! Something happened that shouldnt have!\nDetails:\n");
    printf(message);
    printf("\n\nProgram Terminated.\n\n");
    exit(-1);
}

void println(char* message) {
    printf(message);
    printf("\n");
}
