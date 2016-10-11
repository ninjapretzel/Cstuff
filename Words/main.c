/*
Jonathan Cohen
Code Reading, 2016
Learning the C Language
Program #6 - Words
Word. Words. Reading files was pretty easy.
I use my List* type as a string here.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint-gcc.h>
#include "../List/list.h"

#define MAX_CHARS 1024
#define DEBUG 0

int main() {
    FILE* file;
    List* chars = newList(sizeof(char));

    char* inputFile = "input.txt";
    char* outputFile = "out.txt";

    if (!(file = fopen(inputFile, "r"))) {
        printf("Opening %s for read failed\nExiting.\n", inputFile);
        return 1;
    }

    char c;
    printf("Reading File\n");
    int32_t alpha, digit, white, punct;
    alpha = digit = white = punct = 0;
    while ((c = fgetc(file)) != EOF) {
        ListAdd(chars, &c);
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            alpha++;
        } else if (c >= '0' && c <= '9') {
            digit++;
        } else if (c == ' ' || c == '\n' || c == '\t') {
            white++;
        } else if (c == '.' || c == '!' || c == '?' ||
                   c == ':' || c == ';' || c == '\'' ||
                   c == '\"') {
            punct++;
        }

    }
    fclose(file);

    char output[MAX_CHARS];
    char* op = output;
    op += snprintf(op, MAX_CHARS, "Read %d characters from file.\n", chars->count);
    op += snprintf(op, MAX_CHARS, "Character counts are:\n");
    op += snprintf(op, MAX_CHARS, "Alpha:\t\t%d\n", alpha);
    op += snprintf(op, MAX_CHARS, "Digit:\t\t%d\n", digit);
    op += snprintf(op, MAX_CHARS, "Whitespace:\t%d\n", white);
    op += snprintf(op, MAX_CHARS, "Punctuation:\t%d\n", punct);
    printf("%s", output);

    if (!(file = fopen(outputFile, "w+"))) {
        printf("Opening %s for write failed\nExiting.\n", outputFile);
        return 2;
    }

    fprintf(file, "%s", output);
    fclose(file);
	killList(chars);
    return 0;
}
