#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint-gcc.h>
#include "list.h";

#define MAX_CHARS 256
#define DEBUG 0

///Struct type containing mean, median, and standard Deviation
typedef struct StatData {
    double mean;
    double median;
    double stdev;
} StatData;

///Conversion to string for StatData type
///Prints the content of the StatData* to the given char*
///     Uses _snprintf
void StatDataToString(char* str, StatData* this) {
    _snprintf(str, MAX_CHARS, "Mean: %f\nMedian: %f\nStDev: %f",
        this->mean, this->median, this->stdev);
}

///Loads data from a file, expected to be a list of numbers, one number per line.
///Returns a List<double>* containing all the numbers that were loaded.
List* loadData(char* filename){
    FILE* fp;
    if (!(fp = fopen(filename, "r"))) {
        #if DEBUG > 0
            printf("LoadData: File [%s] not found.\n", filename);
        #endif // DEBUG
        return NULL;
    }
    List* list = newList(sizeof(double));
    char c[MAX_CHARS];
    while (fgets(c, MAX_CHARS-1, fp)) {
        char* last = NULL;
        double val;
        if (!(val = strtod(c, &last)) && *c != '0') {
            #if DEBUG > 0
                printf("LoadData: Failed to load number, skipping line ::%s", c);
            #endif // DEBUG
            continue;
        }
        #if DEBUG > 0
            if (*last == '\n' || *last == ' ') {
                printf("LoadData: Read [%f]\n", val);
            } else {
                printf("LoadData: Done [%f]\n", val);
            }
        #endif // DEBUG

        ListAdd(list, &val);
    }

    fclose(fp);
    return list;
}

///Comparison function used in qsort() to sort doubles
int dcmp(const void* v1, const void* v2) {
    const double* a = v1;
    const double* b = v2;
    return (*a)-(*b);
}
///Processes a set of data to calculate the mean, median, and standard deviation.
///Sorts the data, calulates the median
///Returns a struct containing the mean, median, and stDev
/// data - data set to look at
/// cnt - number of elements in data set
StatData* process(List* list) {
    double* data = (double*) list->data;
    int32_t cnt = list->count;
    //If data is a null pointer, or count is not valid, return nothing.
    if (!data || cnt <= 0) { return NULL; }
    StatData* stats = malloc(sizeof(StatData));
    if (!stats) { return NULL; }

    if (cnt == 1) { // Quickly handle one element
        stats->mean = data[0];
        stats->median = data[0];
        stats->stdev = 0;
        return stats;
    }
    if (cnt == 2) { // Quickly handle two elements
        double avg = (data[0] + data[1]) / 2.0;
        stats->mean = avg;
        stats->median = avg;
        double v1 = (data[0]-avg);
        double v2 = (data[1]-avg);
        stats->stdev = sqrt((v1*v1+v2*v2)/2.0);
        return stats;
    }

    //More elements must be sorted to properly pull out the median...
    qsort(data, cnt, sizeof(double), dcmp);

    //Sum and take mean of elements
    double sum = 0;
    int i;
    for (i = 0; i < cnt; i++) { sum += data[i]; }
    double mean = sum / (double)cnt;
    stats->mean = mean;

    //Take Standard Deviation of elements
    sum = 0;
    for (i = 0; i < cnt; i++) { double v = data[i] - mean; sum += v*v; }
    double stdev = sqrt(sum / ((double)cnt));
    stats->stdev = stdev;

    //Take median of elements
    if (cnt&1) {    // Odd number of elements, just use the value of middle element.
        stats->median = data[cnt/2];
    } else {        // Even number of elements, use the average of middle two elements.
        stats->median = (data[cnt/2] + data[1+cnt/2]) / 2.0;
    }

    return stats;
}




int main() {
    char* inputFile = "numbers.txt";
    char* outputFile = "output.dat";
    printf("Loading file [%s]\n", inputFile);
    List* list = loadData(inputFile);
    printf("Loaded file, contained %d numbers\n", list->count);

    printf("Processing loaded data...\n");
    StatData* stats = process(list);
    char output[MAX_CHARS];
    StatDataToString(output, stats);
    printf("Processed data successfully\n%s\n", output);
    printf("Writing data file [%s]\n", outputFile);

    FILE* fp = fopen(outputFile, "w+");
    if (fp != NULL) {
        fprintf(fp, "%s", output);
        fclose(fp);
        printf("Successfully wrote output!\n");
    } else {

        printf("Failed to open output file.\n");
    }


    return 0;
}






















