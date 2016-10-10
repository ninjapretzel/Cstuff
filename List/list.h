#include <stdint-gcc.h>
#ifndef LIST_INC
#define LIST_INC
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
///Returns the element in the list at position index
void* ListGet(List* this, int32_t index);

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
int32_t ListEnsureCapacity(List* this, int32_t capacity);

///Adds a single element to a List.
///Adds the element by
///Returns:
/// if successful, the new count of the List
/// if unsuccessful, -1
/// this - List to add element to
/// elem - pointer to data to add to the list
int ListAdd(List* this, void* elem);

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
List* newList_cap(size_t size, int32_t initCapacity);

///Creates a new List object with a given size and capacity of 10.
///Returns the pointer to the newly created list data
///Equivelent to the call newList(size, 16);
///If allocation fails, returns a null.
List* newList(size_t size);

///Properly deconstructs and frees memory of a list object.
void killList(List* this);

#endif // LIST_INC
