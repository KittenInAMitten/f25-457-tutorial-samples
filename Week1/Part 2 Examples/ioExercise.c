#include <stdio.h>
/**
 * Collection of io usage and exercises.
 * Authored by Christian Salvador
 */

// In the second half of the main function, there is unfinished code.
// Uncomment this if you want to try and finish it!

int main(int argc, char *argv[]) {
    
    printf("--------Attempting to read standard input (stdio).\n");

    printf("If you want to try throwing a file in via './ioExercise < ioExampleFile.txt', you can try that! Otherwise, type a random string if this pauses here!\n");

    // The following code section shows example usage of scanf and fgets.
    // While scanf will return EOF (-1) when a file ends when a text file is provided as input, fgets stops every newline or at max length provided, or at EOF as well.
    
    // EXERCISE 1: Try to print out the additional in the text file AND have proper exception handling. fgets and scanf do have returns!
    //              There is also an 'ioExampleFileWithMoreLines.txt' file to test that you're handling EOF and looping, and not just copy and pasting the following section.
    
    char scanBuffer;
    // scanf will read depending on the formatting you provide. In this case, it reads for chars
    scanf(" %c", &scanBuffer);

    // printf prints to standard output or stdout
    printf("First character: %c\n", scanBuffer);
    
    //fgets will read up to the newline, or the max length provided, whichever is smallest.
    // fgets here is used to read from standard input or stdin
    char fgetsBuff[128] = "";
    fgets(fgetsBuff, 127, stdin);

    printf("Rest of line is: %s", fgetsBuff);
    printf("\n");

    // -----------FILE USAGE OUTSIDE OF STDIN ----------

    // Declaring a FILE pointer

    FILE *inFile;
    
    printf("--------Attempting to read using FileIO now.\n");

    // EXERCISE 2: Try uncommenting the macro #define FILEIO_EXERCISE_FLAG to activate extra code and see if you can have it read, copy and 
    // write to an output file. I purposefully left it unfinished but it should give you an idea of how to finish it.
    // You can try piecing together the code provided that reads and outputs the fixed input file.

    // #define FILEIO_EXERCISE_FLAG

    #ifdef FILEIO_EXERCISE_FLAG
    {

        FILE *outFile;

        if(argc < 3) {
            printf("EXERCISE 2 UNCOMMENTED. Correct usage is now: ./ioExercise \"sourceFile\" \"destinationFile\"\n");
            return 1;
        }

        if((inFile = fopen(argv[1], "r")) == NULL) {
            printf("Cannot find input file.\n");
            return 1;
        }

        // This only checks for the existence of the file. You may alter this or add another check to get the output file running.
        if((outFile = fopen(argv[1], "r")) != NULL) {
            printf("Output file already exists.\n");
            return 1;
        }

        // 

    }
    #endif

    #ifndef FILEIO_EXERCISE_FLAG
    {

        //CHECK to see if file can be opened.
        // There are different modes:
        // "r" denotes read. File must exist.
        // "w" creates an empty file. CAUTION: This will overwrite a file. You may use "r" to check a file first.
        // "a" appends to the end of an existing file or creates one if it doesn't exist.
        // "r+"/"w+"/"a+" allow for both input and output. The side notes above apply to their respective modes

        char *inputFileString = "./ioExampleFile.txt";

        if((inFile = fopen(inputFileString, "r")) == NULL) {
            printf("If you're not tackling exercise 2, then you must have the 'ioExampleFile.txt' in the same folder as this program!\n");
            return 1;
        }

        // Just like the stdio example, I use the file version of scanf, fscanf, to read the first character.
        fscanf(inFile, " %c", &scanBuffer);

        // a file printf also exists, but I am only printing it out to stdout for this example. Exercise 2 will require something different.
        fprintf(stdout, "First character: %c\n", scanBuffer);

        // fgetc is also a char reader. It will output EOF at the end of file.
        scanBuffer = fgetc(inFile);

        printf("Second character: ");

        // fputc is a char outputer
        fputc(scanBuffer, stdout);

        printf("\n");

        // Using fgets for the input file as well.
        fgets(fgetsBuff, 127, inFile);

        printf("%s\n", fgetsBuff);
        
        // Make sure to close the file at the end.
        fclose(inFile);
    }
    #endif



}