/**
 * Functions to demonstrated shared memory.
 * Authored by Christian Salvador.
 * 
 * sharedMem function from Slide Supplements on D2L
 * 
 * To read outputs, simply uncomment the desired function in main.
 */

#include <stdio.h>
#include <string.h> // for strcpy
#include <sys/ipc.h> // for IPC
#include <sys/shm.h> // For shared memory functions
#include <unistd.h> // For pid_t type
#include <sys/types.h> // For fork()
#include <stdlib.h> // For exit()
#include <sys/wait.h> // for wait()

/**
 * ===================================================================
 * Function taken from Slides Supplements to demonstrate Shared Memory
 * ===================================================================
 */
void sharedMem () {
    // Generates an IPC key. For A1, you will not need  
    //      to use ftok, you can just use IPC_PRIVATE.
    // key_t key = ftok("shmfile", 65);
    // int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
    // Notice string was created before fork.
    char *str = (char*) shmat(shmid, NULL, 0);

    pid_t pid = fork();

    if (pid == 0) {
        sleep(1);
        printf("Child read: %s\n", str);
        strcpy(str, "Child was here!");
        printf("Child wrote: %s\n", str);
		_exit(0);
    } else {
        strcpy(str, "Hello from parent!");
        printf("Parent wrote: %s\n", str);
        wait(NULL);
        printf("Parent sees after child: %s\n", str);
		// Detach then mark the shared memory for removal.
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }
}

/**
 * A function that demonstrates race conditions.
 */
void shmRaceConditions() {
    // Function copied from sharedMem()
    int shmid = shmget(IPC_PRIVATE, 2, 0666 | IPC_CREAT);
    // Notice num was created before fork.
    int *num = (int*) shmat(shmid, NULL, 0);

    num[0] = 3;

    pid_t pid = fork();

    // This is a simulation using sleep to demonstrate a gap in time
    // between a process reading the variable and then incrementing it.
    // The child will sleep for 1 second, while the parent will sleep for 2.
    // Both processes have read num[0] immediately.
    int numRead = num[0];
    if (pid == 0) {
        printf("Child sees num[0]: %d\n", num[0]);
        printf("Child prepares to increment it...\n\n");
        sleep(1);
        num[0] = numRead + 1;
        printf("Child incremented num[0].\n");
        printf("Child now reads num[0]: %d\n\n", num[0]);
		_exit(0);
    } else {
        printf("Parent sees num[0]: %d\n", num[0]);
        printf("Parent prepares to increment it...\n\n");
        sleep(2);
        num[0] = numRead + 1;
        printf("Parent incremented num[0].\n");
        printf("Parent now reads num[0]: %d\n", num[0]);
        wait(NULL);
		// Detach then mark the shared memory for removal.
        shmdt(num);
        shmctl(shmid, IPC_RMID, NULL);
    }
}

int main() {

	printf("If nothing happens, you need to uncomment the function you want to run in main!\n");

    // sharedMem();

    // shmRaceConditions();

    return 0;
}