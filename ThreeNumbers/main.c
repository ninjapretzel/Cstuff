/*
Jonathan Cohen
Code Reading, 2016
Learning the C Language 
Program #2 - ThreeNumbers

Pretty easy. standard input/output.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

///Get a value from the user
double getval(char* prompt) {
    char c[MAX_CHARS];
    char* last = NULL;
    double val;
	
	//Woo, goto and labels! Now I'll never use them again!
loop:
    last = NULL;
    memset(c, 0, MAX_CHARS);
    printf("\n%s\n>", prompt);
    if (!fgets(c, MAX_CHARS-1, stdin)) { goto loop; }
    val = strtod(c, &last);

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

