#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include "../List/list.h"
#include "node.h"

///Reads the next word from a file
///Returns a List<char> containing the word (and ending with a '\0')
///If there are no more words, returns a null pointer
List* nextWord(FILE* file) {
    List* word = newList_cap(sizeof(char), 32);
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c >= 'A' && c <= 'Z') { c += 32; }///Change to lower case.

        if (c >= 'a' && c <= 'z') {
            ListAdd(word, &c);
        } else {
            if (word->count == 0) { continue; }
            char end = 0;
            ListAdd(word, &end);
            return word;
        }
    }
    if (word->count == 0) { killList(word); return NULL; }

    return word;
}

Node* max(Node* from) {
    if (from == NULL) { return NULL; }

    Node* lmax = max(from->left);
    Node* rmax = max(from->right);
    if (lmax && rmax) {
        if (lmax->count > rmax->count) {
            return (from->count > lmax->count) ? from : lmax;
        } else {
            return (from->count > rmax->count) ? from : rmax;
        }
    }
    if (lmax) { return (from->count > lmax->count) ? from : lmax; }
    if (rmax) { return (from->count > rmax->count) ? from : rmax; }

    return from;
}
Node* min(Node* from) {
    if (from == NULL) { return NULL; }

    Node* lmin = min(from->left);
    Node* rmin = min(from->right);
    if (lmin && rmin) {
        if (lmin->count < rmin->count) {
            return (from->count < lmin->count) ? from : lmin;
        } else {
            return (from->count < rmin->count) ? from : rmin;
        }
    }
    if (lmin) { return (from->count < lmin->count) ? from : lmin; }
    if (rmin) { return (from->count < rmin->count) ? from : rmin; }

    return from;
}
int main() {
    FILE* file;
    char* inputFile = "filler.txt";
    char* outputFile = "out.txt";

    if (!(file = fopen(inputFile, "r"))) {
        printf("Could not open file %s for reading", inputFile);
        return 1;
    }
    int32_t pos = ftell(file);
    int32_t last = -1;
    int32_t cnt = 0;
    Node* root = NULL;

    while (pos != last) {
        List* word = nextWord(file);
        if (word == NULL) { break; }
        if (word->count > 0){
            cnt++;
        }
        root = NodeAdd(root, word);
        //killList(word);

        last = pos;
        pos = ftell(file);
    }
    fclose(file);
    printf("Read %d words\n\n", cnt);

    //printf("here is the tree:\n");
    //NodePrintPre(root);

    //printf("\n\nBalancing tree...\n\n");
    //root = NodeBalance(root);
    //printf("\n\nDone balancing!\n\n");

    NodeNicePrint(stdout, root);

    printf("\n\nWriting file.\n\n");
    if (!(file = fopen(outputFile, "w+"))) {
        printf("Could not open file %s for writing", outputFile);
        return 2;
    }

    fprintf(file, "Report of words found:\n");

    int32_t i = 0;
    for (i = 0; i < 33; i++) { fprintf(file, "-"); }

    fprintf(file, "\n");
    NodeNicePrint(file, root);

    for (i = 0; i < 33; i++) { fprintf(file, "-"); }

    fprintf(file, "\n");
    fprintf(file, "Word with Minimum Count:\n");
    NodeSoloPrint(file, min(root));

    fprintf(file, "\n");
    fprintf(file, "Word with Maximum Count:\n");
    NodeSoloPrint(file, max(root));

    fclose(file);

    printf("Done\n");

    return 0;
}



























