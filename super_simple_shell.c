#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Affiche les arguments passés au programme
void display_arguments(int ac, char** av) {
    int i = 0;
    while (av[i] != NULL) {
        printf("%s\n", av[i]);
        i++;
    }
}

// Affiche l'utilisation du programme
void display_usage(char* program_name) {
    printf("Usage: %s <command>\n", program_name);
}

// Exécute une commande spécifique
void execute_command(char* command) {
    pid_t my_pid;
    pid_t child_pid = 1;
    int i = 0;
    int status;
    char* argv[] = { "/bin/sh", "-c", command, NULL }; // Utilisation de /bin/sh pour interpréter la commande

    my_pid = getpid();

    while (i <= 4 && (child_pid != 0)) {
        child_pid = fork();
        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        wait(&status);
        i++;
    }

    if (child_pid == 0) {
        printf("ID child: %u\n\n ID father: %u\n", getpid(), getppid());
        printf(" \n\n");
    } else {
        printf("%u I'm your father: %u\n", my_pid, child_pid);
    }

    if (execvp(argv[0], argv) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Afficher les instructions d'utilisation
    display_usage("program_name");

    // Lire la commande depuis l'entrée standard
    printf("$ ");
    read = getline(&line, &len, stdin);
    if (read == -1) {
        perror("getline");
        exit(EXIT_FAILURE);
    }

    // Supprimer le saut de ligne à la fin de la commande
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    // Exécuter la commande
    execute_command(line);

    free(line);
    return 0;
}
