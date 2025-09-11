#include <stdio.h>
#include <stdlib.h> // <--- Required to use memory allocation functions
#include <string.h>

/**
 * Example memory allocation usage.
 * Authored by Christian Salvador
 */

struct ExampleStruct {
    int intNum;
    double doubleNum;
    float floatNum;
};

void mallocIntro() {
    // Declaring a ptr reserves memory for the pointer to hold an address, but not memory for its buffer.
    int *mallocPtr;

    // Manually allocating memory allows users to dynamically allocate memory.
    // Memory is allocated during runtime, rather than reserved at compilation.
    // Using array[] to declare an array will put it on the stack but its memory allocation cannot be altered.

    // variables not using malloc will be put on the stack and will be freed when the function ends.

    // memory manually allocated goes to the heap and must be freed by the programmer.
    
    // NOTE: Always keep a record of your pointer array size, unless you have an element that is designated as the
    // end of an array like Strings ('\0'), the pointer will not know how big its allocation is by itself.
    unsigned int arraySize = 5;

    mallocPtr = (int *)malloc(sizeof(int) * arraySize);

    // When malloc cannot allocate memory, it will return a NULL pointer that can be checked for
    if(mallocPtr == NULL) {
        printf("Malloc did not allocate memory properly.");
    };
    
    // Using a loop to fill the malloc'd array
    for(int i = 0; i < arraySize; i++) { *(mallocPtr + i) = i + 1;}

    printf("Array holds: { ");
    for(int i = 0; i < arraySize; i++) { printf("%d ", *(mallocPtr + i));}
    printf("}\n");

    arraySize = 10;

    //alloc(size) exists but is not supported by gcc. It is similar to malloc and initializes buffer to zeros.

    // Realloc can resize an array. be sure to use a temp pointer to check if it failed.
    // Otherwise, if it does fail, you may lose the original address and essentially the entire memory block.
    int *reallocTemp = (int *)realloc(mallocPtr, arraySize * sizeof(int));

    if(reallocTemp == NULL) {
        printf("Realloc did not allocate memory properly.");
    };
    
    mallocPtr = reallocTemp;

    // Using a loop to fill the rest of array, it will hold the same values as before, but shrinking may truncate data. 
    for(int i = 5; i < arraySize; i++) { *(mallocPtr + i) = i + 1;}

    printf("Re-allocated array holds: { ");
    for(int i = 0; i < arraySize; i++) { printf("%d ", *(mallocPtr + i));}
    printf("}\n");

    // You can still access and write memory past the set memory allocation but there is no guarantee it will be overwritten!!

    // Make sure to free memory when you're done
    free(mallocPtr);

    struct ExampleStruct* structArrayPtr;

    // An alternative to Alloc is Calloc, it can be used to zero out buffer and initialize data for objects such as structs.
    structArrayPtr = (struct ExampleStruct*)calloc(arraySize, sizeof(struct ExampleStruct));
    printf("Struct size: %ld\n", sizeof(struct ExampleStruct));
    printf("Struct array first object address:  %p\n", structArrayPtr);
    printf("Struct array second object address: %p\n", &*(structArrayPtr + 1));

    // Again, free the memory
    free(structArrayPtr);
}

int main() {

    printf("\n------------Memory Allocation-------------\n\n");
    mallocIntro();

}