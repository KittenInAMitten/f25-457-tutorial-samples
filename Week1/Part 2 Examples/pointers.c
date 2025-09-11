#include <stdio.h>
#include <string.h>
// A colletcion of example usage of material covered for week 1, tutorial 2 material
// Authored by Christian Salvador

void conversionAndCasting() {
    // Generally, casting from type to and from same # of bytes, C can automatically convert
    // I.e., float = int, or double = int;

    int intNum = 3;
    printf("The value of 'intNum' is:       %d\n", intNum);

    float floatNum = (float)intNum;
    printf("The value of 'floatNum' is:     %f\n", floatNum);

    double doubleNum = intNum;
    printf("The value of 'doubleNum' is:    %f\n", doubleNum);
}

void ptrIntro() {
    int num = 9;

    // (type) *(variableName) =... Denotes a declaration of a pointer variable
    int *ptr;

    // '&' is an operator to get the MEMORY ADDRESS of a variable.
    // Notice how ptr has no '*' when initializing its value.
    ptr = &num;

    // When printing, ptr now holds the ADDRESS of num.
    printf("The value of 'ptr' is:  %p\n", ptr);
    printf("The value of '&num' is: %p\n", &num);

    // When used outside of declaration, '*' has a different meaning!
    // '*' means to dereference. It is used to get the value that is at that memory address block. 
    printf("The value of '*ptr' is: %d\n", *ptr);
    printf("The value of 'num' is:  %d\n", num);
}

// The parameters with *(argument) act as declaring a pointer as well.
void swap(int *a_ptr, int *b_ptr) {
    // register tells the compiler to put this variable in a register for faster access in certain cases.
    register int temp;

    // Using '*', we can manipulate the variable via the pointer
    temp = *a_ptr;
    *a_ptr = *b_ptr;
    *b_ptr = temp;
}

void ptrsAndFuncs() {
    //When passing arguments into afunction expecting pointers, we can use '&' to do so.
    int a = 10;
    int b = 5;
    printf("Before swap - 'a':          %d\n", a);
    printf("Before swap - 'b':          %d\n", b);

    printf("---Running swap func where a and b swap values\n");

    // Here we pass in the ADDRESSES of a and b
    swap(&a, &b);

    printf("After function - 'a':       %d\n", a);
    printf("After function - 'b':       %d\n", b);

    // Pointers can also point at functions! You can also ignore parameter names
    void (*ptrFunc)(int*, int*) = &swap;


    // Here we do the same as using ptrsAndFuncsHelper but with our new ptr.
    ptrFunc(&a, &b);
    
    printf("---Running func above but via pointer!\n");
    printf("After ptr function - 'a':   %d\n", a);
    printf("After ptr function - 'b':   %d\n\n", b);
};

void ptrsAndArrays() {
    // Arrays and pointers are practically the same thing! Declared arrays will sit on the stack, while pointers may point to something on stack or heap.
    // The name of the array essentially acts as a pointer to the first element!
    char charArray[5] = "bob!";

    printf("Example string char charArray[5] = 'bob!' or charArray[5] = {'b', 'o', 'b', '!', '\\0'}\n\n");

    // Here, we can see that the elements and addresses of the ptr and the start of the array are the same
    printf("Char from using 'charArray[0]': %c\n", charArray[0]);
    printf("Char from using '*charArray':   %c\n", *charArray);
    printf("charArray address:              %p\n", charArray);
    printf("&charArray[0] address:          %p\n\n", &charArray[0]);
    
    // Using pointer arithmetic, you can access elements. but make sure the entire arithmetic operation is encapsulated by '*'
    printf("Char from using 'charArray[3]':     %c\n", charArray[3]);
    printf("Char from using '*(charArray + 3)': %c\n", *(charArray + 3));
    printf("Char from using '(*charArray) + 3': %c\n\n", (*charArray) + 3);

    // The memory addresses are also dependent on the data type size, just like a pointer.
    // Char byte size = 1
    printf("charArray[0] address:       %p\n", &charArray[0]);
    printf("charArray[1] address:       %p\n", &charArray[1]);
    printf("(*charArray) address:       %p\n", (charArray));
    printf("*(charArray + 1) address:   %p\n\n",  (charArray + 1));

    // Example using int byte size of 4.
    int intArray[3] = {1,2,3};
    
    printf("intArray[0] address:       %p\n", &intArray[0]);
    printf("intArray[1] address:       %p\n", &intArray[1]);
    printf("intArray[2] address:       %p\n", &intArray[2]);
    printf("(*intArray) address:       %p\n", (intArray));
    printf("*(intArray + 1) address:   %p\n",  (intArray + 1));
    printf("*(intArray + 2) address:   %p\n",  (intArray + 2));
}

void cStrings() {

    // There is no built-in String data type in C
    // Strings are just char arrays that always end in NULL or the '\0' character. Useful for finding the end of a string!

    char test[] = "test";
    char *ptrTest = "test";

    printf("What is printed when we do 'char test[] = \"test\"':    %s\n", test);
    printf("What is printed when we do 'char *ptrTest = \"test\"':  %s\n", ptrTest);

    // Looping through the string can expose the '\0' or NULL character but will not show as an actual character.
    printf("Printing out individual characters: ");
    for (int i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
        printf("'%c', ", test[i]);
    }
    printf("\n");

    // To update a declared string, you must either use strcpy(array, "string") or update each char element one by one and ensure it ends in \0
    // You must also ensure that the size of the destination array can fit the incoming array.
    // strcpy is provided by the <string.h> header which has useful functions to manipulate strings.
    char testCopy[5];
    strcpy(testCopy, test);
    printf("What is printed when we do 'char testCopy[5]; strcpy(testCopy, test);': %s\n", testCopy);
}

int main() {
    printf("\n------------Conversion And Casting-------------\n\n");
    conversionAndCasting();

    printf("\n------------Pointers Intro-------------\n\n");
    ptrIntro();

    printf("\n------------Pointers And Functions-------------\n\n");
    ptrsAndFuncs();

    printf("\n------------Pointers And Arrays-------------\n\n");
    ptrsAndArrays();

    printf("\n------------C Strings-------------\n\n");
    cStrings();

    return 0;
}