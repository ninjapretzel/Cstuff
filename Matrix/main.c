#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <time.h>
#include <limits.h>
#include "list.h"

void printMat(void* mat, int32_t rows, int32_t cols) {
    int32_t* matrix = mat;
    int32_t i;
    int32_t length = rows * cols;
    for (i = 0; i < length; i++) {
        if (i % cols == 0) { printf("[ "); }
        printf("%2d  ", matrix[i]);
        if (i % cols == (cols-1)) { printf("]\n"); }
    }
}

int32_t min(void* mat, int32_t rows, int32_t cols) {
    int32_t* matrix = mat;
    int32_t length = rows * cols;
    int32_t min = INT_MAX;
    int32_t i;
    for (i = 0; i < length; i++) {
        if (matrix[i] < min) { min = matrix[i]; }
    }
    return min;
}

int32_t max(void* mat, int32_t rows, int32_t cols) {
    int32_t* matrix = mat;
    int32_t length = rows * cols;
    int32_t max = INT_MIN;
    int32_t i;
    for (i = 0; i < length; i++) {
        if (matrix[i] > max) { max = matrix[i]; }
    }
    return max;
}

typedef struct Pair {
    int32_t val;
    int32_t count;
} Pair;

void incrementCount(List* list, int32_t value) {
    if (list == NULL) { return; }

    int32_t i;
    for (i = 0; i < list->count; i++) {
        Pair* p = list->data;
        p += i;
        if (p->count == 0 && p->val == 0) { printf("somehow accessed an empty element..."); }
        if (p->val == value) {
            p->count += 1;
            return;
        }
    }

    Pair p;
    p.val = value;
    p.count = 1;
    ListAdd(list, &p);

}

List* countOccurances(void* mat, int32_t rows, int32_t cols) {
    int32_t* matrix = mat;
    printf("Test");
    int32_t length = rows * cols;
    printf("Test %d", length);
    List* list = newList(sizeof(Pair));
    printf("Got a new list");

    int32_t i;
    for (i = 0; i < length; i++) {
        int32_t val = *(matrix+i);
        //printf("Counting value %d", val);
        incrementCount(list, val);
    }

    return list;
}

void printPairList(List* list) {
    int32_t i;
    double numVals = 0;
    printf("Printing list of pairs...\n");
    for (i = 0; i < list->count; i++) {
        Pair* p = ListGet(list, i);
        numVals += p->count;
    }
    for (i = 0; i < list->count; i++) {
        Pair* p = ListGet(list, i);
        double percentOcc = 100.0 * ((double)p->count) / numVals;
        printf("\t%d\t:%d\t ( %.2f%c )\n", p->val, p->count, percentOcc, '%');
    }
    printf("end of list\n");
}

#define ROWS 20
#define COLS 10
int main() {
    int32_t matrix[ROWS][COLS];
    srand(time(NULL));
    int32_t r, c;

    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            int v = 7 + rand() % 5 ;
            matrix[r][c] = v;
        }
    }
    printMat(matrix, ROWS, COLS);
    printf("Done printing\n");

    List* pairs = countOccurances(matrix, ROWS, COLS);
    printf("Done counting\n");
    printPairList(pairs);

    return 0;
}
