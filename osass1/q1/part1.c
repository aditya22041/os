#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr,"fork failed");
        exit(1);
    } 
    else if (child_pid == 0) { // Child process
        printf("C) Child is having ID %d\n", getpid());//pid for current process i.e child
        printf("D) My Parent ID is %d\n", getppid());//for parent id
    } 
    else { // Parent process
        printf("A)Parent (P) is having ID %d\n", getpid());

        // Wait for the child process to complete before proceeding
        wait(&status);

        printf("B) ID of P’s Child is %d\n", child_pid);
    }

    return 0;
}
