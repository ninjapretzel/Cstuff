#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

double getval(char* prompt) {
    char c[MAX_CHARS];
    char* last = NULL;
    double val;
loop:
    last = NULL;
    memset(c, 0, MAX_CHARS);
    printf("\n%s\n>", prompt);
    if (!fgets(c, MAX_CHARS-1, stdin)) { goto loop; }
    val = strtod(c, &last);
    //printf("\nRead:%s",c);
    //printf("\nptr:0x%x", last);
    //printf("\nchar:0x[%x]", *last);

    if (!val && *c != '0') { printf("\nPlease enter an actual number."); goto loop; }
    if (*last != '\n') { printf("\nPlease enter just a number."); goto loop; }

    return val;
}

int main() {
    double aval, bval, cval;

    printf("Welcome to this stupid program\n");
    printf("It calculates the sum and average of 3 numbers.\n");

    aval = getval("Enter the first value");
    bval = getval("Enter the second value");
    cval = getval("Enter the third value");

    double sum = aval + bval + cval;
    double avg = sum / 3.0;

    printf("\n\nThe sum is %f\nThe average is %f", sum, avg);

    return 0;
}

