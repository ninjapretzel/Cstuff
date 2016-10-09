
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint-gcc.h>

#include "list.h"

///Grabs an element from a List, at index.
///If given invalid parameters, returns a NULL (NULL list or out of range index)
void* ListGet(List* this, int32_t index) {
    if (!this) { return NULL; }
    if (index < 0 || index >= (this->count)) { return NULL; }
    uint8_t* pt = (uint8_t*)this->data;
    pt += index * this->size;
    return (void*) pt;
}

///Ensures a list has at least a certain amount of capacity.
///Will only increase the capacity of a list. Will not decrease capacity.
///Memory of increased capacity will be memset to 0 as uint8_t
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

    //New total length (in uint8_t's)
    int32_t length = capacity * this->size;
    //Old total length (in uint8_t's)
    int32_t oldLength = this->capacity * this->size;
    //Additional length (in uint8_t's)
    int32_t addLength = length - oldLength;

    uint8_t* array = (uint8_t*) realloc(this->data, length);
    if (array != NULL) {
        this->data = array;
        this->capacity = capacity;
        uint8_t* oldEnd = array + oldLength;
        memset(oldEnd, 0, addLength);
        return 0;
    }
    return -3;
}

///Adds a single element to a List.
///Adds the element by copying its data into the list.
///Returns:
/// if successful, the new count of the List
/// if unsuccessful, -1
/// this - List to add element to
/// elem - pointer to data to add to the list
int ListAdd(List* this, void* elem) {
    if (this->capacity == this->count) {
        #ifdef DEBUG
        #if DEBUG > 0
            printf("ListAdd: Resizing capacity from %d to %d\n", this->capacity, 2 * this->capacity);
        #endif // DEBUG > 0
        #endif // DEBUG
        if (ListEnsureCapacity(this, (this->capacity)*2) < 0) { return -1; }
    }
    uint8_t* ray = (uint8_t*) this->data;
    size_t size = this->size;
    uint8_t* position = ray + (size * this->count);
    uint8_t* elemData = (uint8_t*)elem;
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
/// size - size of a single element in the list (in uint8_ts)
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
    memset(data, 0, size * initCapacity);

    list->size = size;
    list->capacity = initCapacity;
    list->count = 0;
    list->data = data;

    return list;
}

///Creates a new List object with a given size and capacity of 10.
///Returns the pointer to the newly created list data
///Equivelent to the call newList(size, 10);
///If allocation fails, returns a null.
List* newList(size_t size) { return newList_cap(size, 10); }
