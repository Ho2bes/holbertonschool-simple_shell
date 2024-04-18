#include "willson.h"
#include "custom_function.c"

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    char *command;
    char *args[2];
    while (1) {
        printf("#cisfun$ ");
        fflush(stdout); // Manually flush stdout
        read = getline(&input, &len, stdin);
        if (read == -1) {
            if (feof(stdin)) {
                printf("\n"); // Print newline after Ctrl+D
                break; // Exit loop on EOF
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }
        // Handle 'exit' command here
        if (strcmp(input, "exit\n") == 0) {
            free(input);
            exit(EXIT_SUCCESS);
        }
        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';
        // Fork a child process
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            // Tokenize the input
            command = strtok(input, " ");
            args[0] = command;
            args[1] = NULL;
            // Execute the command
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                _exit(EXIT_FAILURE); // Use _exit to avoid flushing buffers
            }
        } else {
            // Parent process
            // Wait for the child process to finish
            wait(NULL);
        }
        // Free allocated memory for input
        free(input);
        input = NULL;
    }
    // Free allocated memory for input before exiting
    free(input);
    return 0;
}
