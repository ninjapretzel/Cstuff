/*
Jonathan Cohen
Code Reading, 2016
Learning the C Language 
Program #4 - QuadraticEquation
This one was pretty easy. Doesn't even need my magic list code.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_CHARS 512

double getval(char* prompt) {
    char c[MAX_CHARS];
    char* last = NULL;
    double val;
	//Guess I'm using gotos/labels again, because I copy/pasted code. Yay.
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

void printEq(double a, double b, double c) {
    printf("{ %fx^2 + %fx + %f = 0 }", a, b, c);
}

int main() {
    double a, b, c;
    printf("Welcome to this quadratic equation program.\n");
    printf("It will solve the roots for { ax^2 + bx + c = 0 }\n");

    a = getval("Enter the value for a");
    b = getval("Enter the value for b");
    c = getval("Enter the value for c");

    if (a) {
        //ax^2 + bx + c
        //-b +/- sqrt(b^2-4ac) / 2a 9
        double innerTerm = b*b - 4*a*c;
        printf("\n\n%f\n\n",innerTerm);
        double bottom = 2 * a;
        if (innerTerm < 0) {
            printf("There are no real roots to ");
            printEq(a, b, c);
            printf("\n");
        } else if (innerTerm == 0) {
            printf("There is one real root to ");
            printEq(a, b, c);
            double root = -b / bottom;
            printf("\n. It is %f\n", root);
        } else {
            double root1 = (-b - sqrt(innerTerm)) / bottom;
            double root2 = (-b + sqrt(innerTerm)) / bottom;
            printf("There are two real roots to ");
            printEq(a, b, c);
            printf("\nThey are %f and %f\n", root1, root2);
        }
    } else { 
		// Extra functionality- doesn't break with linear equations or constant equations.
        if (b) {
            printf("That's a linear equation!");
            //bx + c = 0
            double x = -c / b;
            printf("The x-axis is crossed at x = %f.\n", x);
        } else {
            printf("That's just a flat line at x=%f!\n", c);
        }
    }

    printf("Done, goodbye.\n");
    return 0;
}