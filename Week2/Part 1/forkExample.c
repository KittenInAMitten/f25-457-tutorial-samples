/**
 * Collection of example fork function usage.
 * Authored by Christian Salvador. Some lines from Slide Supplements.
 * 
 * To read outputs, simply uncomment the desired function in main.
 */

#include <stdio.h>
#include <unistd.h> // For pid_t type
#include <sys/types.h> // For fork()
#include <stdlib.h> // For exit()
#include <sys/wait.h> // for wait()

/**
 * Function that demonstrates waiting
 */
void waiting() {
    pid_t child;
    // Standard loop and fork handling
    for(int i = 0; i < 5; i++) {
        child = fork();
        if(child < 0) {
            fprintf(stderr, "Fork Failed.");
            exit(-1);
        }
        else if(child == 0) {
            if(i == 1) sleep(1); //sleeping 1
            printf("     PID %d terminating.\n", getpid());
            _exit(0);
        }
    }
    sleep(2);
    // Loop to read first 3 from the terminated list
    for(int i = 0; i < 3; i++) {
        child = wait(NULL);
        printf("%d. Child PID %d termination read.\n", i, child);
    }
    // Loop to clear out children
    while(wait(NULL) != -1);
}

/**
 * Function that demonstrates reading process exit status.
 */
void waitStatus() {
    pid_t child;
    // Standard loop and fork handling
    for(int i = 0; i < 3; i++) {
        child = fork();
        if(child < 0) {
            fprintf(stderr, "Fork Failed.");
            exit(-1);
        }
        else if(child == 0) {
            printf("    Child %d exiting with code: %d\n", 
                        getpid(), i - 1);
            _exit((i - 1));
        }
    }
    sleep(1); // Sleep to give child time
    int wstatus;
    // Loop through each child and read status.
    for(int i = 0; i < 3; i++) {
        child = wait(&wstatus);
        printf("Child PID %d returned with code %d.\n", 
                child, WEXITSTATUS(wstatus));
    }
}

// Function that demonstrates pointers in forked processes.
void forkPointer() {
    int num = 3;
    int *numPtr = &num;
	printf("Parent: numPtr is %p with value is %d\n\n", 
            numPtr, *numPtr);
    // Standard fork creation and handling
	pid_t child = fork();
	if(child < 0) {
		fprintf(stderr, "Fork Failed.");
		exit(-1);
	}
    // The child process will read, write and read through the pointer.
	else if(child == 0) {
		printf("Child:  numPtr is %p with value %d\n", 
                numPtr, *numPtr);
		printf("Child:  Running *numPtr = 5;\n");
        *numPtr = 5;
		printf("Child:  numPtr is %p with value %d\n", 
                numPtr, *numPtr);
		_exit(0);
	}
    // The parent will sleep and then try reading the value through pointer.
	else {
		sleep(1);
		wait(NULL);
	    printf("\nParent: numPtr is %p with value is %d\n", 
                numPtr, *numPtr);
	}
}

/**
 * Function that demonstrates the PID returned from fork();
 */
void forkAndPID() {
	pid_t childID_1;

    // Standard fork creating and handling
	childID_1 = fork();
	if(childID_1 < 0) { // If fork fails, exit.
		fprintf(stderr, "Fork Failed.");
		exit(-1);
	}
	else if(childID_1 == 0) { // If its 0, its the child
		printf("Child Process - childID_1 is: %d\n", childID_1);
		_exit(0);
	}
	else { // If its bigger than 0, it's the parent
		printf("Parent Process - childID_1 is: %d\n", childID_1);
	}
}

/**
 * Function that demonstrates forking after forking after forking aft-
 */
void forkAfterFork() {
	fork();
	fork();
	fork();
	printf("I'm a process!\n");
	exit(0); // Purposefully exiting even the main thread.
}

/**
 * Function that demonstrates how variables are unaffected by other 
 * process changes.
 */
void forkStates() {
	int num = 5;
	printf("Parent: num is %d\n", num);
    // Standard fork creation and handling
	pid_t child = fork();
	if(child < 0) {
		fprintf(stderr, "Fork Failed.");
		exit(-1);
	}
    // I have the child sleep to give time to the parent to modify num
	else if(child == 0) {
		printf("Child: num is %d\n", num);
		sleep(1);
		printf("Child: num is now %d\n", num);
		_exit(0);
	}
    // I have the parent update the variable
	else {
		num = 10;
		printf("Parent: num is now %d\n", num);
		wait(NULL);
		printf("Parent: Child is done.\n");
	}
}

int main() {
	
	printf("If nothing happens, you need to uncomment the function you want to run in main!\n");

	// forkAndPID();

	// forkStates();

    // waiting();

    // waitStatus();

    // forkPointer();

	// forkAfterFork(); // This will prematurely exit, so any functions called after will not be called when this runs.

	return 0;
}

