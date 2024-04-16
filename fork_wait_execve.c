#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;

    printf("Parent process running...\n");
    for (i = 0; i < 5; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error:");
            return 1;
        } else if (pid == 0) {
            // Child process
            printf("Child process %d running...\n", i+1);
            execlp("ls", "ls", "-l", "/tmp", NULL);
            perror("Error:");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            wait(&status);
            printf("Child process %d exited with status %d\n", i+1, WEXITSTATUS(status));
        }
    }

    printf("All child processes have exited.\n");

    return 0;
}
