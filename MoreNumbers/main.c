#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint-gcc.h>
typedef uint8_t byte;

#define MAX_CHARS 256
#define DEBUG 0


///Typedef for byte (unsigned 8 bit number)

///"""""GENERIC""""" array data struct
///Should be endian-independent
typedef struct List {
    ///Size of an element in the given array
    size_t size;
    ///Total capacity allocated for the current array
    int32_t capacity;
    ///Current count of elements in the current array
    int32_t count;
    ///Data Array pointer
    void* data;
} List;

///Grabs an element from a List, at index.
///If given invalid parameters, returns a NULL (NULL list or out of range index)
void* ListGet(List* this, int32_t index) {
    if (!this) { return NULL; }
    if (index < 0 || index >= (this->count)) { return NULL; }
    byte* pt = (byte*)this->data;
    pt += index * this->size;
    return (void*) pt;
}

///Ensures a list has at least a certain amount of capacity.
///Will only increase the capacity of a list. Will not decrease capacity.
///Memory of increased capacity will be memset to 0 as byte
///Returns:
///     0 on success
///     -1 if given any invalid parameters
///     -2 if given capacity is smaller than current capacity
///     -3 if realloc fails
/// this - List to operate on
/// capacity - capacity to ensure.
int32_t ListEnsureCapacity(List* this, int32_t capacity) {
    if (capacity < 0) { return -1;}
    if (capacity <= this->capacity) { return -2; }

    //New total length (in bytes)
    int32_t length = capacity * this->size;
    //Old total length (in bytes)
    int32_t oldLength = this->capacity * this->size;
    //Additional length (in bytes)
    int32_t addLength = length - oldLength;

    byte* array = (byte*) realloc(this->data, length);
    if (array != NULL) {
        this->data = array;
        this->capacity = capacity;
        byte* oldEnd = array + oldLength;
        memset(oldEnd, 0, addLength);
        return 0;
    }
    return -3;
}

///Adds a single element to a List.
///Adds the element by
///Returns:
/// if successful, the new count of the List
/// if unsuccessful, -1
/// this - List to add element to
/// elem - pointer to data to add to the list
int ListAdd(List* this, void* elem) {
    if (this->capacity == this->count) {
        #if DEBUG > 0
            printf("ListAdd: Resizing capacity from %d to %d\n", this->capacity, 2 * this->capacity);
        #endif // DEBUG
        if (ListEnsureCapacity(this, (this->capacity)*2) < 0) { return -1; }
    }
    byte* ray = (byte*) this->data;
    size_t size = this->size;
    byte* position = ray + (this->size * this->count);
    byte* elemData = (byte*)elem;
    int i;
    for (i = 0; i < size; i++) {
        position[i] = elemData[i];
    }

    this->count+=1;
    return this->count;
}

///Creates a new List object with a given size and capacity.
///Returns the pointer to the newly created list data.
///New list has members:
///     size of the given size
///     capacity of the list equal to initCapacity
///     count of 0
///     newly allocated array, memset contain all zeros.
///If allocation fails, returns a null.
/// size - size of a single element in the list (in bytes)
/// initialCapacity - number of initial slots for data elements in allocated array.
List* newList_cap(size_t size, int32_t initCapacity) {
    if (initCapacity <= 0 || size == 0) { return NULL; }

    List* list = malloc(sizeof(List));
    void* data = malloc(size * initCapacity);
    if (!data || !list) {
        free(data);
        free(list);
        return NULL;
    }

    list->size = size;
    list->capacity = initCapacity;
    list->count = 0;
    list->data = data;
    memset(data, 0, size * list->capacity);

    return list;
}

///Creates a new List object with a given size and capacity of 10.
///Returns the pointer to the newly created list data
///Equivelent to the call newList(size, 10);
///If allocation fails, returns a null.
List* newList(size_t size) { return newList_cap(size, 10); }

///Struct containing mean, median, and standard Deviation
typedef struct StatData {
    double mean;
    double median;
    double stdev;
} StatData;

void StatDataToString(char* str, StatData* this) {
    _snprintf(str, MAX_CHARS, "Mean: %f\nMedian: %f\nStDev: %f",
        this->mean, this->median, this->stdev);
}

///Extra Feature: Array resizing!
///Resize an array, and nullify the new elements of the resized array.
///Modifies the memory at *cap with the new capacity of the array.
///Returns the updated pointer of the array.
/// ray - pointer to array to resize
/// cap - initial capacity of the array (in elements)
/// sz - the size of each element of the array (in bytes)
void* resizeArray(void* ray, int* cap, int sz) {
    int newCap = 2 * (*cap);
    #if DEBUG > 0
        printf("Resizing an array from %d x %d bytes to %d x %d bytes", *cap, sz, newCap, sz);
    #endif // DEBUG
    uint8_t* newRay = (uint8_t*) realloc(ray, newCap * sz);
    uint8_t* oldEnd = newRay + *cap * sz;
    memset(oldEnd, 0, *cap * sz);
    *cap = newCap;
    return newRay;
}
int dcmp(const void* v1, const void* v2) {
    const double* a = v1;
    const double* b = v2;
    return (*a)-(*b);
}

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
///Processes a set of data to calculate the mean, median, and standard deviation.
///Sorts the data, calulates the median
///Returns a struct containing the mean, median, and stDev
/// data - data set to look at
/// cnt - number of elements in data set
StatData* process(double* data, int cnt) {
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
    StatData* stats = process(list->data, list->count);
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






















